# SCouple
Single, a couple in disguise.

#### What is SCouple?
`SCouple`disguises a singly linked list as a doubly linked list.

#### What is the heart and soul of SCouple?
xor-logic. It couples previous and next nodes of a given node, together. The coupled address is stored in that given node's link. So, to obtain its next node, a node's link will be xor-ed with its previous node and with its next node for its previous node. For the first node, link will be just second node. For the last node, link will be just last but one node.

#### What is special?
`SCouple` is more than just a disguised doubly linked list. The metadata of the list is ubiquitous. Metadata of the list is maintained as a single instance to which each node of the list points to. Metadata includes number of nodes, head, tail, middle node, previous to middle node, data operations, and atomic support.

#### How intuitive and user-friendly is SCouple?
`SCouple` has a comprehensive automated test-suite that's user-friendly due to its intuitive and eye-pleasing color codes. It performs all the list operations using randomly generated data sets. As a quality measure, `valgrind` has been used to confirm that the code is leak-free.

Below snapshots indicate an automated test run. They cover all of the existing list operations with randomly generated data in an automated fashion. They are self-explanatory with the diagnostic messages in them for each list operation. The middle node is highlighted with curly braces, `{}`. First two are of non-debug modes and last on is from debug mode. In debug mode, even the addresses of the node and the respective data are displayed in that order, to quicken the debugging!

![Snap 1](https://github.com/RaghavanSanthanam/SCouple/blob/master/snaps/1.png)
![Snap 2](https://github.com/RaghavanSanthanam/SCouple/blob/master/snaps/2.png)
![Snap 3](https://github.com/RaghavanSanthanam/SCouple/blob/master/snaps/3.png)


#### Can SCouples be independent?
`SCouple` supports atomicity. Metadata includes a `pthread_mutex` to make list operations atomic. Macro `__ATOMIC_SUPPORT__` helps in this. Lists can be atomicized while getting created or later. Same holds good for de-atomicizing when needed.

#### How is data managed?
`SCouple` allows user to have data of any type and define the applicable data operations. Each node will point to user data. And data operations are pointed by metdata. Data operations are convinently abstracted as an interface.

#### How scalable SCouple is?
`SCouple` with its per-list metadata is as scalable as any other standard list implementaions.

#### How different is SCouple?
`SCouple` implements the standard list operations and more with carefully crafted algorithms that account for the complex xor-based link manipulations each time when a node gets rearranged or removed. Good news is that APIs provided for performing list operations are so well-defined that user need not bother about the internals of the complex implementation.

#### What operations does SCouple support?
`SCouple` has a standard set of list operations and more that make it a powerful tool to manipulate a singly linked list just like a doubly linked list. On a need basis, more operations will be incorporated to the below set.
* Add node
* Delete node
* Sort list data(with nodes in-place)
* Sort list nodes as well with data
* Print list
* Reverse list
* Swap halves
* Join two lists
* Halve a list
* Slice a list from given m to n
* Braid two lists
* Spiralify a list
* Nth node
* Data of nth node
* Find a node with given data
* Simplify a SCouple list into simple singly linked list
* Print simple list
* Update metadata(middle node/previous to middle node)

#### How is SCouple organized?
* Data operations   : `dataops/*`
* Common primitives : `libcommon/*`
* SCouple implementation : `libscouple/scouple.*`
* SCouple atomic support : `libscouple/atomic.*`
* Simple list implementation : `libscouple/simple.*`
* Automated test suite(also supports manual mode) : `test/int.c`
* Test script : `starttests.sh`

#### What are the steps to follow to build SCouple?
    mkdir SCouple
    cd SCouple # Get the code into this folder
    make or make all # non-debug and non-atomic binaries.
    make atomic # non-debug atomic binaries.
    make debug # debug non-atomic binaries.
    make debugatomic # debug and atomic binaries
    make every # combines all of the above - for testing all builds

#### How to test SCouple?
After buidling, just run `starttests.sh` from `SCouple` folder.

#### Any points to keep in mind?
`SCouple` has been developed and tested on Ubuntu 14.04 LTS(x86_64).
C compiler used is gcc v4.9.2. Having said that, `SCouple`, logically, 
will build and run on any modern platform with the necessary environment.
As such there is no platform-dependency. Only the test suite uses ASCII
color codes for appealing the users with neat display. So, the platforms
that won't support ASCII color codes might see raw escape sequences like
`[32m`, etc - these are controlled by the color-specific macros in
`libcommon/common.h` and they can be conditionally compiled out if needed -
currently, this `NO_COLOR` support is absent and user can easily include
the same in `libcommon/common.h` when needed.











