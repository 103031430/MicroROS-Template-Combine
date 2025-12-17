#ifndef DATATYPE_H
#define DATATYPE_H

enum DataType {
    INT,
    DOUBLE,
    BOOL
};

struct AnyValue {
    DataType type;

};

#endif // INT_PUBLISHER_H