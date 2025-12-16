#ifndef DATATYPE_H
#define DATATYPE_H

enum DataType {
    INT32,
    DOUBLE,
    BOOL
};

struct AnyValue {
    DataType type;

};

#endif // INT_PUBLISHER_H