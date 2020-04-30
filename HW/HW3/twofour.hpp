
// Our TwoFourTree superclass
template <typename T>
class TwoFourTree {

    public:
        //Gets the number of data nodes within the tree and subtrees
        virtual int size() const = 0;
};

// TwoNode child node
template <typename T>
class TwoNode: public TwoFourTree<T> {

    public:
        TwoNode(const T& a) {
            data = a;
            lNode = nullptr;
            rNode = nullptr;
        };

        //Copy Constructor
        TwoNode(const T& a, TwoFourTree<T>* t1, TwoFourTree<T>* t2) {
            data = a;
            lNode = t1;
            rNode = t2;
        };

        int size() const {
            int sz = 1;
            if (lNode) {sz += lNode->size();}
            if (rNode) {sz += rNode->size();}
            return sz;
        };

    private:
        T data;
        TwoFourTree<T>* lNode;
        TwoFourTree<T>* rNode;

};

// ThreeNode child node
template <typename T>
class ThreeNode: public TwoFourTree<T> {

    public:
        ThreeNode(const T& a, const T& b) {
            data1 = a;
            data2 = b;
            lNode = nullptr;
            cNode = nullptr;
            rNode = nullptr;
        };

        //Copy Constructor
        ThreeNode(const T& a, const T& b, TwoFourTree<T>* t1, TwoFourTree<T>* t2, TwoFourTree<T>* t3) {
            data1 = a;
            data2 = b;
            lNode = t1;
            cNode = t2;
            rNode = t3;
        };

        int size() const {
            int sz = 2;
            if (lNode) {sz += lNode->size();}
            if (cNode) {sz += cNode->size();}
            if (rNode) {sz += rNode->size();}
            return sz;
        };

    private:
        T data1;
        T data2;
        TwoFourTree<T>* lNode;
        TwoFourTree<T>* cNode;
        TwoFourTree<T>* rNode;

};

// FourNode child node
template <typename T>
class FourNode: public TwoFourTree<T> {

    private:
        T data1;
        T data2;
        T data3;
        TwoFourTree<T>* llNode;
        TwoFourTree<T>* lNode;
        TwoFourTree<T>* rNode;
        TwoFourTree<T>* rrNode;

    public:
        FourNode(const T& a, const T& b, const T& c) {
            data1 = a;
            data2 = b;
            data3 = c;
            llNode = nullptr;
            lNode = nullptr;
            rNode = nullptr;
            rrNode = nullptr;
        };

        //Copy Constructor
        FourNode(const T& a, const T& b, const T& c, TwoFourTree<T>* t1, TwoFourTree<T>* t2, TwoFourTree<T>* t3, TwoFourTree<T>* t4) {
            data1 = a;
            data2 = b;
            data3 = c;
            llNode = t1;
            lNode = t2;
            rNode = t3;
            rrNode = t4;
        };

        int size() const {
            int sz = 3;
            if (llNode) {sz += llNode->size();}
            if (lNode) {sz += lNode->size();}
            if (rNode) {sz += rNode->size();}
            if (rrNode) {sz += rrNode->size();}
            return sz;
        };

};