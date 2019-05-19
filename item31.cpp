// reference: http://jatinganhotra.com/blog/2012/11/25/forward-class-declaration-in-c-plus-plus/

//
// You can use forward declarations in all the following cases, where<Paste>
//

class Master {
private:
    // Declare a member to be a pointer or a reference to the incomplete type
    Forward *ptr1;     
    Forward &ptr2;

public:

    // Declare functions or methods which accepts/return incomplete types:
    void ByValue(Forward by_value);
    Forward OrReturnValue();

    // Define functions or methods which accepts/return pointers/references 
    // to the incomplete type (but without using its members):
    void OrByPointer(Forward* by_pointer);
    void OrByReference(const Forward& by_reference);
    Forward& ReturnByRef();
    Forward* ReturnByPointer();

};

//
// You can’t use forward declarations in all the following cases, where
//

// Use it as a base class
class Master : Forward {} // compiler error!

// Use it to declare a member:
class Master {
    Forward cannot_define_obj_member; // compiler error!
};

// Define functions or methods using the incomplete type
void SomeFunc1(Forward x) {} // compiler error!
Forward    SomeFunc2()    {} // compiler error!

// Use its methods or fields, in fact trying to dereference a variable with incomplete type
class Master {
    Forward *forward_class_ptr;            
    void SomeFunc()            
    {
        forward_class_ptr->SomeMethod();      // compiler error!
        int i = forward_class_ptr->SomeField; // compiler error!
    }
};

// Whenever you use a class as a template parameter, the declaration of that class must be complete and not simply forward declared.
class Master {
      std::vector<Forward> some_stl_containers_;
};


// Delete the forward declared class in the module
class Forward;
class Master
{
    void SomeFunc(Forward* forward_class_ptr)
    {
        delete forward_class_ptr;
    }
};
// From the C++ standard: 5.3.5/5:
// "If the object being deleted has incomplete class type at the point of deletion and the complete class has a // non-trivial destructor or a deallocation function, the behavior is undefined."
// e.g gcc 4.2.1 errors out and reports a note: neither the destructor nor the class-specific operator delete will be called, even if they are declared when the class is defined.
