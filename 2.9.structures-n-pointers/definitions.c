// structure is a composite data type containing a collection of variables or data objects
// is allocated a piece of contiguous memory
// individual fields accessed using the . operator
// at runtime each field is accessed as an offset from the starting address of the structure

struct node {
  struct node *next;
  int key;
  char name[64] 
};

// use as derived type to define variables
struct node x; *nodePtr;

// alternatively use typedef statement
typedef struct node2 {
  struct node2 *next;
  int key;
  char name[64];
}NODE2;

// Then NODE is a derived type used to define variables of that type
NODE2 y, *node2Ptr;

// given two structures of the same type NODE x,y; can assign x to y by y = x
// the compiler generated code uses the lib function memncpy(&y, &x, sizeof(NODE)) to copy the entire structure

// the compiler calculates the size in total number of bytes of the structure
// due to memory alignment constraints, compiler may pad some of the fields of the structure with extra bytes
// user may define structure with the PACKED attribute, which prevents the compiler padding
typedef struct node3 {
  struct node2 *next;
  int key;
  char name[64];
}__attribute__((packed, aligned(1))) NODE3;
// in the above case, size of NODE3 structure will be 10bytes
// without the packed attribute, would be 12bytes as the compiler would pad the name field with
// 2 extra bytes


// Pointers
// are variables which point to other data objects i.e. contain the address of other data objects
// defined with the * attribute i.e. TYPE *ptr where TYPE can be base or derived type

NODE2 z, *p;
p = &z; // asign addr of x to p
// then *p denotes the object z whose memers can be accessed as
// (*p).name, (*p).value, (*p).next
// alternatively z members can be referenced with the point at operator, ->
// p->name, p->value, p->next
