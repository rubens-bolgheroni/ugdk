#ifndef UGDK_FILESYSTEM_FILE_H_
#define UGDK_FILESYSTEM_FILE_H_

#include <ugdk/filesystem.h>
#include <ugdk/structure/types.h>
#include <cstddef>

namespace ugdk {
namespace filesystem {

enum class SeekPositions {
    BEGINNING, CURRENT, END
};

class File {
  public:
    virtual ~File() {}

    /**
    * @return The size of this file, or -1 if unknown.
    */
    virtual int64 size() const = 0;

    /**
    * Seek to an offset of whence.
    * @param offset The offset to the given location.
    * @param whence One of the SeekPositions.
    * @return The final offset in the file stream, relative to the start. -1 if an error occured.
    */
    virtual int64 Seek(int64 offset, SeekPositions whence) = 0;

    /**
    * @return The current offset in the file stream, relative to the start.
    */
    int64 Tell();

    /** 
    * Reads up to maxnum blocks of the given size and save at ptr.
    * @param ptr The buffer where the data will be saved.
    * @param size The size of each memory block to be read, in bytes.
    * @param maxnum The maximum number of blocks to be read.
    * @return The number of blocks read, or 0 if end of file or error.
    */
    virtual std::size_t ReadRaw(void* ptr, std::size_t size, std::size_t maxnum) = 0;

    /**
    * Reads up to maxnum objects of type T and save at ptr.
    * @param ptr The buffer where the objects will be saved.
    * @param maxnum The maximum number of objects to be read.
    * @return The number of objects read, or 0 if end of file or error.
    */
    template <class T>
    std::size_t Read(T* ptr, std::size_t maxnum = 1) {
        return ReadRaw(ptr, sizeof(T), maxnum);
    }

    /**
    * Writes num blocks of the given size from ptr.
    * @param ptr The buffer from where the data is read.
    * @param size The size of each memory block to be written, in bytes.
    * @param maxnum The maximum number of blocks to be written.
    * @return The number of blocks written, or 0 if end of file or error.
    */
    virtual std::size_t WriteRaw(const void* ptr, std::size_t size, std::size_t num) = 0;

    /**
    * Writes num objects of type T from ptr.
    * @param ptr The buffer from where the objects are read.
    * @param num The number of objects to write.
    * @return The number of objects written, or 0 if end of file or error.
    */
    template <class T>
    std::size_t Write(const T* ptr, std::size_t num = 1) {
        return WriteRaw(ptr, sizeof(T), num);
    }

  protected:
    File() {}    
};

}  // namespace filesystem
}  // namespace ugdk

#endif  // UGDK_FILESYSTEM_FILE_H_
