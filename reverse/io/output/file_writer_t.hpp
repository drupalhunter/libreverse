#ifndef FILE_WRITER_H_
#define FILE_WRITER_H_

#include <fstream>
#include <input/File_ID.hpp>
#include <input/File_Base.hpp>
#include <input/IOException.hpp>
#include <gmpxx.h>
#include <boost/cstdint.hpp>
#include <filters/FilterException.hpp>

namespace io {

  /*!
   * \todo Revisit this class when we have a reason to write our data out to a file
   */
  template <typename Data_Type>
  class File_Writer
  {
  public:

    File_Writer (File_ID* file_ref,
		 Data_Type* data);

    virtual ~File_Writer ();

    inline void file_Op (mpf_class val, std::string errstr);

    inline void file_Op_Str (std::string val, std::string errstr);

    inline void file_Op_Write (boost::uint32_t val, std::string errstr);
 
    /*!
     * \brief Pass in new data to be processed
     * \param data Input Data
     */
    virtual void write_data (void) = 0;

    File_ID* get_File();

    void write_Timestamp (mpf_class& obj);

    /*!
     * \brief Write the binary data to the file
     * \param data Data to be written to the file
     */
    void write (boost::uint32_t* data);

  protected:
    Data_Type* m_data;

    /*! \brief Reference to the write file handle */
    std::ofstream m_file_handle;

    /*! \brief File identification */
    File_ID* m_file_ref;

  private:
    File_Writer (){}
  };

#include "File_Writer_T.inl"

} /* namespace io */

#include "File_Writer_T.cpp"

#endif /* FILE_WRITER_H_ */
