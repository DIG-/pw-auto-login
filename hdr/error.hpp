#pragma once

namespace DIG {

typedef enum {
  OK = 0,
  NOT_IMPLEMENTED = 1,
  CAN_NOT_CREATE_FOLDER = 2,
  CAN_NOT_OPEN_FILE = 3,
  FILE_DOES_NOT_EXISTS = 4,
} Err;

}