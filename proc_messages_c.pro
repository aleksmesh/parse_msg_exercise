TEMPLATE = app
TARGET = test
INCLUDEPATH += .

SOURCES = test.c                    \
          crc32.c                   \
          input_file_generator.c    \
          mes_hex.c                 \
          process_messages.c

HEADERS = crc32.h                   \
          input_file_generator.h    \
          mes_hex.h                 \
          process_messages.h        \
          constants.h
