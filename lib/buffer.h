

class Buffer {
 private:
  char *buf;           /* Buffer for data. */
  unsigned int alloc;  /* Number of bytes allocated for data. */
  unsigned int offset; /* Offset of first byte containing data. */
  unsigned int end;    /* Offset of last byte containing data. */

 public:
  Buffer(){};
  void init() {
    alloc = 32768;
    buf = (char *)malloc(alloc);
    offset = 0;
    end = 0;
  }
  ~Buffer() {
    printf("buffer destroyed!\n");
    free(buf);
  }
  void clear() {
    offset = 0;
    end = 0;
  }
  char *get_buf() { return buf; }
  int length() { return end - offset; }
  void get(char *buffer, unsigned int len) {
    if (len > end - offset) {
      printf("buffer_get: trying to get more bytes than in buffer");
      exit(1);
    }

    memcpy(buffer, buf + offset, len);
    offset += len;
  }
  void consume(unsigned int len) {
    if (len > end - offset) {
      printf("buffer_get: trying to get more bytes than in buffer");
      exit(1);
    }
    offset += len;
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
        // printf("======== MEMMOVE =========\n");
        continue;
      }
      /* Increase the size of the buffer and retry. */
      alloc += len + 32768;
      // printf("======== REALLOC %d =========\n", alloc);
      buf = (char *)realloc(buf, alloc);
    }
  }
};