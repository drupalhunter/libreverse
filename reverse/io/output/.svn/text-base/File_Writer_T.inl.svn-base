template <typename Data_Type>
inline void File_Writer<Data_Type>::file_Op (mpf_class val,
                                             std::string errstr)
  ACE_THROW_SPEC((kurt::KURT_IOException))
{
  m_file_handle << val << '\0';
  if (! File_Base::file_ready(&m_file_handle))
    {
      std::stringstream error;
      error << "Error writing: " << errstr << std::endl;
      ACE_THROW(KURT_IOException(((error).str()).c_str()));
    }
}

template <typename Data_Type>
inline void File_Writer<Data_Type>::file_Op_Str (std::string val,
                                                 std::string errstr)
  ACE_THROW_SPEC((kurt::KURT_IOException))
{
  m_file_handle << val << '\0';
  if (! File_Base::file_ready(&m_file_handle))
    {
      std::stringstream error;
      error << "Error writing: " << errstr << std::endl;
      ACE_THROW(KURT_IOException(((error).str()).c_str()));
    }
}

template <typename Data_Type>
inline void File_Writer<Data_Type>::file_Op_Write (boost::uint32_t val,
                                                   std::string errstr)
  ACE_THROW_SPEC((kurt::KURT_IOException))
{
    write(&val);
    if (!File_Base::file_ready(&m_file_handle))
    {
      std::stringstream error;
      error << "Error writing: " << errstr << std::endl;
      ACE_THROW(KURT_IOException(((error).str()).c_str()));
    }
}
