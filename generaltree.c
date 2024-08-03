#include <stdio.h>
#include <stdlib.h>
 
struct TNODE
{
    char label; // nhãn của nút
    struct TNODE *firstChild, *nextSibling;
};
 
// hàm tạo nút mới
struct TNODE *createNewNode(char label)
{
    struct TNODE *newNode = (struct TNODE*)malloc(sizeof(struct TNODE));
    newNode->label = label;
    newNode->firstChild=NULL;
    newNode->nextSibling=NULL;
    return newNode;
}
 
// hàm này sẽ thêm 1 con mới nhãn là label cho nút hiện tại root
// nếu root chưa có con thì nút mới sẽ là firstChild
// ngược lại, nó sẽ là con út tiếp
// root phải khác NULL
void addNewChild(struct TNODE *root, char label)
{
    struct TNODE *newNode = createNewNode(label);
    // nếu chưa có con
    if(root->firstChild==NULL)
    {
        root->firstChild = newNode;
    }
    else
    {
        // đã có con, cần tìm con cuối cùng hiện tại
        struct TNODE *prevBrother = root->firstChild;
        while(prevBrother->nextSibling!=NULL){
            prevBrother=prevBrother->nextSibling;
        }
        // thêm nút mới là người anh em tiếp
        prevBrother->nextSibling = newNode;
    }
}
// hàm khởi tạo cây
struct TNODE *initTree()
{
    // gốc cây là A
    struct TNODE *root = createNewNode('A');
    // thêm B, D, F, K là con của A theo đúng thứ tự
    addNewChild(root,'B');
    addNewChild(root,'D');
    addNewChild(root,'F');
    addNewChild(root,'K');
    // thêm C là con của B (root->firstChild)
    addNewChild(root->firstChild,'C');
    // thêm E,G là con của F (root->firstChild->nextSibling->nextSibling)
    struct TNODE *cRoot = root->firstChild->nextSibling->nextSibling;
    addNewChild(cRoot,'E');
    addNewChild(cRoot,'G');
    // thêm H,I là con của G (root->firstChild->nextSibling->nextSibling->firstChild->nextSibling)
    cRoot = root->firstChild->nextSibling->nextSibling->firstChild->nextSibling;
    addNewChild(cRoot,'H');
    addNewChild(cRoot,'I');
    // thêm J là con của H (root->firstChild->nextSibling->nextSibling->firstChild->nextSibling->firstChild)
    cRoot = cRoot->firstChild;
    addNewChild(cRoot,'J');
    return root;
}
 
void preOrder(struct TNODE *root)
{
    if(root==NULL) return;
    printf("%c, ", root->label);
    struct TNODE *nextChild = root->firstChild;
    while(nextChild!=NULL)
    {
        preOrder(nextChild);
        nextChild=nextChild->nextSibling;
    }
}
// duyệt theo thứu tự sau
void postOrder(struct TNODE *root)
{
    if(root==NULL) return;

    struct TNODE *nextChild = root->firstChild;
    while(nextChild!=NULL)
    {
        postOrder(nextChild);
        nextChild=nextChild->nextSibling;
    }
    printf("%c, ", root->label);
}
// tìm chiều cao của 1 nút trên cây
int getHeight(struct TNODE *root)
{
    // nếu nút rỗng
    if(root==NULL) return -1;
    // nếu nút là nút lá
    if(root->firstChild==NULL) return 0;
    // đi tìm chiều cao cây con lớn nhất
    int maxHeight = 0, childHeight;
    struct TNODE *nextChild = root->firstChild;
    while (nextChild!=NULL)
    {
        childHeight = getHeight(nextChild);
        // cập nhật lại chiều cao cây con lớn nhất
        if(childHeight>maxHeight){
            maxHeight=childHeight;
        }
        nextChild=nextChild->nextSibling;
    }
    // chiều cao của gốc sẽ là chiều cao cây con lớn nhất + 1 nút
    return 1+maxHeight;
}
 
// đếm số lượng nút trên cây
int countNodes(struct TNODE *root)
{
    // nếu nút rỗng
    if(root==NULL) return 0;
    int totalChildrenNodes =0;
    struct TNODE *nextChild = root->firstChild;
    while (nextChild!=NULL)
    {
        totalChildrenNodes += countNodes(nextChild);
        nextChild=nextChild->nextSibling;
    }
    return 1+totalChildrenNodes;
}
int main()
{
    struct TNODE *root = initTree();
    printf("Duyet cay theo thu tu truoc: ");
    preOrder(root);
    printf("\n");
    printf("Duyet cay theo thu tu truoc: ");
    postOrder(root);
    printf("\n");
    printf("Chiều cao %c : %d\n",root->label, getHeight(root));
    struct TNODE *cRoot = root->firstChild->nextSibling;
    printf("Chiều cao %c : %d\n",cRoot->label, getHeight(cRoot));
    printf("Số nút con : %d\n",countNodes(root));
    return 0;
}
