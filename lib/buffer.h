

class Buffer {
 private:
  char *buf;           /* Buffer for data. */
  unsigned int alloc;  /* Number of bytes allocated for data. */
  unsigned int offset; /* Offset of first byte containing data. */
  unsigned int end;    /* Offset of last byte containing data. */

 public:
  Buffer() {
    alloc = 4096;
    buf = (char *)malloc(alloc);
    offset = 0;
    end = 0;
  }
  ~Buffer() { free(buf); }
  void clear() {
    offset = 0;
    end = 0;
  }
  void append(const char *data, unsigned int len) {
    char *cp;
    append_space(&cp, len);
    memcpy(cp, data, len);
  }
  void append_space(char **datap, unsigned int len) {
    /* If the buffer is empty, start using it from the beginning. */
    if (offset == end) {
      offset = 0;
      end = 0;
    }

    while (1) {
      /* If there is enough space to store all data, store it now. */
      if (end + len < alloc) {
        *datap = buf + end;
        end += len;
        return;
      }
      /*
       * If the buffer is quite empty, but all data is at the end, move the
       * data to the beginning and retry.
       */
      if (offset > alloc / 2) {
        memmove(buf, buf + offset, end - offset);
        end -= offset;
        offset = 0;
        continue;
      }
      /* Increase the size of the buffer and retry. */
      alloc += len + 32768;
      buf = (char *)realloc(buf, alloc);
    }
  }
};