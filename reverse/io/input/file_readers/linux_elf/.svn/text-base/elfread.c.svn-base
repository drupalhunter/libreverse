#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "elfread_aux.h"
#include "elfread.h"

/* Yes, I know that <elf.h> exists; but this is a learning exercise. */

#define RESULT_OF_TOO_MANY_BLOGGERS sht[i].sh_size/sht[i].sh_entsize

FILE *f;
FILE *errstream;

void (*readObj)(void *, int);

void normalRead(void *obj, int sz) {
   fread(obj,1,sz,f);
}

void reverseRead(void *obj, int sz) {
   char tmp[sz], *o = (char*)obj;
   fread(tmp,1,sz,f);
   for (int i = 0; i < sz; i++)
      o[i] = tmp[sz-i-1];
}

// void read_ELF_header(Elf32_Ehdr*) {{{
void read_ELF_header(Elf32_Ehdr *h) {
   fread(h->e_ident,1,EI_NIDENT,f);
   // Data encoding {{{
   switch (h->e_ident[EI_DATA]) {
      case ELFDATA2LSB: {
            unsigned int test = 0x01020304;
            if (test & 0xff == 0x04) { /* MSB-last storage */
               readObj = reverseRead;
            } else {
               readObj = normalRead;
            }
        }
        break;
      case ELFDATA2MSB: {
            unsigned int test = 0x01020304;
            if (test & 0xff == 0x04) { /* MSB-last storage */
               readObj = normalRead;
            } else {
               readObj = reverseRead;
            }
        }
        break;
      case ELFDATANONE:
        fprintf(errstream,"No valid data encoding specified\n");
        exit(0);
      default:
        fprintf(errstream,"I don't understand the data encoding '%i'\n",h->e_ident[EI_DATA]);
        exit(0);
   }
   // }}}
   readObj(&h->e_type,sizeof(Elf32_Half));
   readObj(&h->e_machine,sizeof(Elf32_Half));
   readObj(&h->e_version,sizeof(Elf32_Word));
   readObj(&h->e_entry,sizeof(Elf32_Addr));
   readObj(&h->e_phoff,sizeof(Elf32_Off));
   readObj(&h->e_shoff,sizeof(Elf32_Off));
   readObj(&h->e_flags,sizeof(Elf32_Word));
   readObj(&h->e_ehsize,sizeof(Elf32_Half));
   readObj(&h->e_phentsize,sizeof(Elf32_Half));
   readObj(&h->e_phnum,sizeof(Elf32_Half));
   readObj(&h->e_shentsize,sizeof(Elf32_Half));
   readObj(&h->e_shnum,sizeof(Elf32_Half));
   readObj(&h->e_shstrndx,sizeof(Elf32_Half));
}
// }}}

// void print_ELF_header(FILE*, Elf32_Ehdr*) {{{
void print_ELF_header(FILE *out, Elf32_Ehdr *h) {
   fprintf(out,"Magic: 0x%x '%c' '%c' '%c'\n",h->e_ident[EI_MAG0],
         h->e_ident[EI_MAG1], h->e_ident[EI_MAG2], h->e_ident[EI_MAG3]);
   switch (h->e_ident[EI_CLASS]) {
      case ELFCLASSNONE: fprintf(out,"Class: Invalid\n"); break;
      case ELFCLASS32: fprintf(out,"Class: 32-bit objects\n"); break;
      case ELFCLASS64: fprintf(out,"Class: 64-bit objects\n"); break;
   }
   switch (h->e_ident[EI_DATA]) {
      case ELFDATANONE: fprintf(out,"Data: Invalid encoding\n"); break;
      case ELFDATA2LSB: fprintf(out,"Data: LSB-last\n"); break;
      case ELFDATA2MSB: fprintf(out,"Data: MSB-last\n"); break;
   }
   fprintf(out,"e_ident[EI_VERSION]: %i\n",h->e_ident[EI_VERSION]);
   switch (h->e_type) {
      case ET_NONE: fprintf(out,"Filetype: None\n"); break;
      case ET_REL: fprintf(out,"Filetype: Relocatable\n"); break;
      case ET_EXEC: fprintf(out,"Filetype: Executable\n"); break;
      case ET_DYN: fprintf(out,"Filetype: Shared object\n"); break;
      case ET_CORE: fprintf(out,"Filetype: Core\n"); break;
      case ET_LOPROC:
      case ET_HIPROC:
                    fprintf(out,"Filetype: Processor-specific\n"); break;
   }
   switch (h->e_machine) {
      case EM_NONE: fprintf(out,"Required architecture: No machine\n"); break;
      case EM_M32: fprintf(out,"Required architecture: AT&T WE 32100\n"); break;
      case EM_SPARC: fprintf(out,"Required architecture: SPARC\n"); break;
      case EM_386: fprintf(out,"Required architecture: Intel 80386\n"); break;
      case EM_68K: fprintf(out,"Required architecture: Motorola 68000\n"); break;
      case EM_88K: fprintf(out,"Required architecture: Motorola 88000\n"); break;
      case EM_860: fprintf(out,"Required architecture: Intel 80860\n"); break;
      case EM_MIPS: fprintf(out,"Required architecture: MIPS RS3000\n"); break;
   }
   fprintf(out,"ELF version: %i\n",h->e_version);
   fprintf(out,"Entry point: 0x%x\n",h->e_entry);
   fprintf(out,"Program header table offset: %i bytes into file\n",h->e_phoff);
   fprintf(out,"Section header table offset: %i bytes into file\n",h->e_shoff);
   fprintf(out,"Processor-specific flags: 0x%x\n",h->e_flags);
   fprintf(out,"Header size: %i bytes\n",h->e_ehsize);
   fprintf(out,"Program header table entry size: %i bytes\n",h->e_phentsize);
   fprintf(out,"Number of program header table entries: %i\n",h->e_phnum);
   fprintf(out,"Section header table entry size: %i bytes\n",h->e_shentsize);
   fprintf(out,"Number of section header table entries: %i\n",h->e_shnum);
   fprintf(out,"Section header table index of section name string table: %i\n",h->e_shstrndx);
}
// }}}

// void read_symbol_table(Elf32_Shdr*) {{{
void read_symbol_table(Elf32_Shdr* sht) {
   // saves and restores file position
   sht->SymTab = malloc(sizeof(Elf32_Sym)*(sht->sh_size/sht->sh_entsize));
   long fpos = ftell(f);
   fseek(f,sht->sh_offset,SEEK_SET);
   Elf32_Sym* st = sht->SymTab; /* Convenience */
   long entries = sht->sh_size/sht->sh_entsize;
   for (int i = 0; i < entries; i++) {
      readObj(&(st[i].st_name),sizeof(Elf32_Word));
      readObj(&(st[i].st_value),sizeof(Elf32_Addr));
      readObj(&(st[i].st_size),sizeof(Elf32_Word));
      readObj(&(st[i].st_info),1);
      readObj(&(st[i].st_other),1);
      readObj(&(st[i].st_shndx),sizeof(Elf32_Half));
   }
   fseek(f,fpos,SEEK_SET);
}
// }}}

// void print_symbol_table(FILE*, Elf32_Ehdr*, Elf32_Shdr*, int index) {{{
void print_symbol_table(FILE* out, Elf32_Ehdr* h, Elf32_Shdr* sht, int i) {
   Elf32_Sym* st = sht[i].SymTab;
   long fpos = ftell(f);
   long entries = RESULT_OF_TOO_MANY_BLOGGERS;
   for (int j = 0; j < entries; j++) {
      fseek(f,sht->sh_offset,SEEK_SET);
      fprintf(out, "\tSymbol: ");
      if (st[j].st_name > 0) {
         fseek(f,sht[sht[i].sh_link].sh_offset+st[j].st_name,SEEK_SET);
         char buf[100];
         fread(buf,1,100,f);
         fprintf(out,"[%s]",buf);
      } else {
         fprintf(out,"[]");
      }
      if (st[j].st_shndx == SHN_COMMON) {
         fprintf(out,", Constraints: %i [Common]",st[j].st_value);
      } else if (st[j].st_shndx == SHN_ABS) {
         fprintf(out,", Absolute: 0x%x (%i)",st[j].st_value,st[j].st_value);
      } else if (st[j].st_shndx == SHN_UNDEF) {
         fprintf(out,", Undefined (%i)\n",st[j].st_value);
         continue;
      } else {
         fprintf(out,", Address: 0x%x (%i)",st[j].st_value,st[j].st_value);
         if (h->e_type == ET_REL) {
            fprintf(out," [Offset, relative to Sec.%i]",st[j].st_shndx);
         } else if (h->e_type == ET_EXEC || h->e_type == ET_DYN) {
            fprintf(out," [Virtual, relative to Sec.%i]",st[j].st_shndx);
         }
      }
      if (st[j].st_size > 0) {
         fprintf(out,", Size: 0x%x (%i)",st[j].st_size,st[j].st_size);
      } else {
         fprintf(out,", Size: Unknown/Irrelevant");
      }
      switch (ELF32_ST_BIND(st[j].st_info)) {
         case STB_LOCAL: fprintf(out,", Bound: Local"); break;
         case STB_GLOBAL: fprintf(out,", Bound: Global"); break;
         case STB_WEAK: fprintf(out,", Bound: WeakGlobal"); break;
         case STB_HIPROC:
         case STB_LOPROC:
                        fprintf(out,", Bound: ProcSpecific"); break;
         default: fprintf(out,", Bound: ???????");
      }
      switch (ELF32_ST_TYPE(st[j].st_info)) {
         case STT_NOTYPE: fprintf(out,", NoType\n"); break;
         case STT_OBJECT: fprintf(out,", DataObject\n"); break;
         case STT_FUNC: fprintf(out,", Function\n"); break;
         case STT_SECTION: fprintf(out,", SectionRef\n"); break;
         case STT_FILE: fprintf(out,", FileRef\n"); break;
         case STT_LOPROC:
         case STT_HIPROC:
                        fprintf(out,", ProcSpecific\n"); break;
         default: fprintf(out,", ???? Type ????\n");
      }
   }
   fseek(f,fpos,SEEK_SET);
}
// }}}

void read_reloc_entries(Elf32_Shdr* sht) {
   // saves and restores file position
   sht->Reloc = malloc(sizeof(Elf32_Rela)*(sht->sh_size/sht->sh_entsize));
   long fpos = ftell(f);
   Elf32_Rela* rel = sht->Reloc; /* Convenience */
   long entries = sht->sh_size/sht->sh_entsize;
   fseek(f,sht->sh_offset,SEEK_SET);
   for (int i = 0; i < entries; i ++) {
      readObj(&(rel[i].r_offset),sizeof(Elf32_Addr));
      readObj(&(rel[i].r_info),sizeof(Elf32_Word));
      if (sht->sh_type == SHT_RELA)
         readObj(&(rel[i].r_addend),sizeof(Elf32_Sword));
   }
   fseek(f,fpos,SEEK_SET);
}

void print_reloc_entries(FILE* out, Elf32_Ehdr *h, Elf32_Shdr *sht, int i) {
   Elf32_Rela *rel = sht[i].Reloc;
   long entries = sht[i].sh_size/sht[i].sh_entsize;
   for (int j = 0; j < entries; j++) {
      fprintf(out,"\tRelocEntry: 0x%x (%i)",rel[j].r_offset,rel[j].r_offset);
      if (h->e_type == ET_REL)
         fprintf(out,"<--Byte offset frob beginning of section to storage unit affected");
      else
         fprintf(out,"<--Virtual address of storage unit affected");
      fprintf(out,", SymTab index: 0x%x (%i)", ELF32_R_SYM(rel[j].r_info),ELF32_R_SYM(rel[j].r_info));
      switch (ELF32_R_TYPE(rel[j].r_info)) {
         case R_386_NONE: fprintf(out,", No relocation"); break;
         case R_386_32: fprintf(out,", S + A relocation"); break;
         case R_386_PC32: fprintf(out,", S + A - P relocation"); break;
         case R_386_GOT32: fprintf(out,", G + A - P relocation"); break;
         case R_386_PLT32: fprintf(out,", L + A - P relocation"); break;
         case R_386_COPY: fprintf(out,", No relocation [copy]"); break;
         case R_386_GLOB_DAT: fprintf(out,", S relocation [GLOB_DAT]"); break;
         case R_386_JMP_SLOT: fprintf(out,", S relocation [JMP_SLOT]"); break;
         case R_386_RELATIVE: fprintf(out,", B + A relocation"); break;
         case R_386_GOTOFF: fprintf(out,", S + A - GOT relocation"); break;
         case R_386_GOTPC: fprintf(out,", GOT + A - P relocation"); break;
         default: fprintf(out,", ???? relocation");
      }
      if (sht->sh_type == SHT_RELA) {
         fprintf(out,", Addend: 0x%x (%i)\n",rel[j].r_addend,rel[j].r_addend);
      } else fprintf(out,"\n");
   }
}


// void read_section_headers(Elf32_Ehdr*, Elf32_Shdr**) {{{
void read_section_headers(Elf32_Ehdr *h, Elf32_Shdr **osht) {
   *osht = (Elf32_Shdr*)malloc(h->e_shnum * h->e_shentsize * sizeof(Elf32_Shdr));
   Elf32_Shdr *sht = *osht;
   for (int i = 0; i < h->e_shnum; i++) {
      fseek(f,h->e_shoff+i*h->e_shentsize,SEEK_SET); /* Get to correct position */
      readObj(&(sht[i].sh_name),sizeof(Elf32_Word));
      readObj(&(sht[i].sh_type),sizeof(Elf32_Word));
      readObj(&(sht[i].sh_flags),sizeof(Elf32_Word));
      readObj(&(sht[i].sh_addr),sizeof(Elf32_Addr));
      readObj(&(sht[i].sh_offset),sizeof(Elf32_Off));
      readObj(&(sht[i].sh_size),sizeof(Elf32_Word));
      readObj(&(sht[i].sh_link),sizeof(Elf32_Word));
      readObj(&(sht[i].sh_info),sizeof(Elf32_Word));
      readObj(&(sht[i].sh_addralign),sizeof(Elf32_Word));
      readObj(&(sht[i].sh_entsize),sizeof(Elf32_Word));
      if (sht[i].sh_type == SHT_SYMTAB || sht[i].sh_type == SHT_DYNSYM) {
         read_symbol_table(&sht[i]);
         sht[i].Reloc = NULL;
      }
      else if (sht[i].sh_type == SHT_RELA || sht[i].sh_type == SHT_REL) {
         read_reloc_entries(&sht[i]);
         sht[i].SymTab = NULL;
      } else {
         sht[i].SymTab = NULL;
         sht[i].Reloc = NULL;
      }
   }
}
// }}}

// void print_section_headers(FILE*, Elf32_Ehdr*, Elf32_Shdr*) {{{
void print_section_headers(FILE *out, Elf32_Ehdr *h, Elf32_Shdr *sht) {
   for (int i = 0; i < h->e_shnum; i++) {
      fprintf(out, "[%i] ",i);
      if (h->e_shstrndx > 0) {
         fseek(f,sht[h->e_shstrndx].sh_offset+sht[i].sh_name,SEEK_SET);
         char buf[100];
         fread(buf,1,100,f);
         fprintf(out,"[%s]\n",buf);
      }
      switch (sht[i].sh_type) {
         case SHT_NULL: fprintf(out,"\tNULL\n"); goto endLoop;
         case SHT_PROGBITS: fprintf(out,"\tPROGBITS"); break;
         case SHT_SYMTAB: fprintf(out,"\tSYMTAB"); break;
         case SHT_STRTAB: fprintf(out,"\tSTRTAB"); break;
         case SHT_RELA: fprintf(out,"\tRELA"); break;
         case SHT_HASH: fprintf(out,"\tHASH"); break;
         case SHT_DYNAMIC: fprintf(out,"\tDYNAMIC"); break;
         case SHT_NOTE: fprintf(out,"\tNOTE"); break;
         case SHT_NOBITS: fprintf(out,"\tNOBITS"); break;
         case SHT_REL: fprintf(out,"\tREL"); break;
         case SHT_SHLIB: fprintf(out,"\tSHLIB"); break;
         case SHT_DYNSYM: fprintf(out,"\tDYNSYM"); break;
         case SHT_LOPROC:
         case SHT_HIPROC:
                          fprintf(out,"\tHI/LOPROC");
         case SHT_LOUSER:
         case SHT_HIUSER:
                          fprintf(out,"\tHI/LOUSER");
         default:
                          fprintf(out,"\tNO_FRICKIN'_IDEA");
      }
      switch (sht[i].sh_flags) {
          case SHF_WRITE|SHF_ALLOC|SHF_EXECINSTR:
             fprintf(out,", WXA"); break;
          case SHF_WRITE|SHF_ALLOC:
             fprintf(out,", WA"); break;
          case SHF_ALLOC|SHF_EXECINSTR:
             fprintf(out,", AX"); break;
          case SHF_WRITE|SHF_EXECINSTR:
             fprintf(out,", WX"); break;
          case SHF_WRITE:
             fprintf(out,", W"); break;
          case SHF_ALLOC:
             fprintf(out,", A"); break;
          case SHF_EXECINSTR:
             fprintf(out,", X"); break;
          default:
             if (sht[i].sh_flags & SHF_MASKPROC)
               fprintf(out,", O");
             else if (sht[i].sh_flags == 0)
               fprintf(out, ", NoFlags");
             else
               fprintf(out,", Flags: ??0x%x??",sht[i].sh_flags);
      }
      fprintf(out, ", Adr: 0x%x (%i)",sht[i].sh_addr,sht[i].sh_addr);
      fprintf(out, ", Ofs: 0x%x (%i)",sht[i].sh_offset,sht[i].sh_offset);
      fprintf(out, ", Sz: 0x%x (%i)",sht[i].sh_size,sht[i].sh_size);
      if (sht[i].sh_addralign <= 1)
         fprintf(out,", NoConstraints");
      else
         fprintf(out,", Constr: %i",sht[i].sh_addralign);
      if (sht[i].sh_type == SHT_DYNAMIC)
         fprintf(out,"\tSection header index of strtab used by section entries: %i\n",sht[i].sh_link);
      else if (sht[i].sh_type == SHT_HASH)
         fprintf(out,"\tSection header index of symtab to which hash table applies: %i\n",sht[i].sh_link);
      else if (sht[i].sh_type == SHT_REL || sht[i].sh_type == SHT_RELA)
         fprintf(out,"\tSection header index of associated symtab: %i\n",sht[i].sh_link);
      else if (sht[i].sh_type == SHT_SYMTAB || sht[i].sh_type == SHT_DYNSYM)
         fprintf(out,"\tSection header index of associated strtab: %d\n",sht[i].sh_link);
      else fprintf(out,"\tsh_link: Undefined\n");
      if (sht[i].sh_type == SHT_RELA || sht[i].sh_type == SHT_REL)
         fprintf(out,"\tSection header index of section to which relocation applies: %i\n",sht[i].sh_info);
      else if (sht[i].sh_type == SHT_SYMTAB || sht[i].sh_type == SHT_DYNSYM)
         fprintf(out,"\tSymbol table index of last local symbol, plus one: %i\n",sht[i].sh_info);
      // else, fprintf(out,"\tsht_info: Undefined\n");
      if (sht[i].sh_entsize != 0)
         fprintf(out,"\tSize of fixed entries: %i\n",sht[i].sh_entsize);
      if (sht[i].sh_type == SHT_SYMTAB || sht[i].sh_type == SHT_DYNSYM) {
         print_symbol_table(out,h,sht,i);
      } else if (sht[i].sh_type == SHT_REL || sht[i].sh_type == SHT_RELA) {
         print_reloc_entries(out,h,sht,i);
      }
      // else, no fixed entries.
endLoop:
      ;
      }
}
// }}}

int main(int argc, char **argv) {
   errstream = stderr;
   Elf32_Ehdr header;
   Elf32_Shdr *sht = NULL;
   if (argc < 2 || !(f = fopen(argv[1],"r"))) {
      return printf("Syntax: %s [filename]\n",argv[0]);
   }
   read_ELF_header(&header);
   if (!(header.e_type&(ET_EXEC|ET_REL|ET_DYN))) return 2;
   print_ELF_header(stdout, &header);
   if (header.e_shoff != 0) {
      read_section_headers(&header, &sht);
      print_section_headers(stdout, &header, sht);
   }
   if (sht) {
      for (int i = 0; i < header.e_shnum; i++) {
         if (sht[i].SymTab) free(sht[i].SymTab);
         if (sht[i].Reloc) free(sht[i].Reloc);
      }
      free(sht);
   }
   fclose(f);
}
