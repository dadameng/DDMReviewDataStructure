#include<stdio.h>  
#include<stdlib.h>  
    
typedef struct AvlNode *Position;  
typedef struct AvlNode *AvlTree;  
typedef int ElementType;  
    
struct AvlNode{  
    ElementType Element;  
    AvlTree Left;  
    AvlTree Right;  
    int Height;  
}AvlNode;  
    
//Avl函数的声明  
AvlTree CreateTree();                                //创建Avl树   
Position Find(ElementType Element, AvlTree T);       //查找   
Position FindMax(AvlTree T);  
Position FindMin(AvlTree T);  
AvlTree Insert(ElementType Element, AvlTree T);      //插入   
AvlTree Delete(ElementType Element, AvlTree T);      //删除   
    
    
//插入结点到AVL树所需的函数声明   
int Height(AvlTree T);                                //返回树的高   
int Max(ElementType A, ElementType B);                //比较树高   
Position LeftLeftRotate(Position K2);                 //左左单旋  (即右旋，顺时针转动)
Position RightRightRotate(Position K2);               //右右单旋  (即左旋，逆时针转动)
Position LeftRightRotate(Position K3);                //左右双旋  (先逆时针，后顺时针) 
Position RightLeftRotate(Position K3);                //右左双旋  (先顺时针，后逆时针)
    
void PreOrder_1(AvlTree T);                           //先序遍历（递归）   
    
int main()  
{  
    AvlTree T;  
    ElementType Element;  
    
    int flag = 1, i;  
        
        printf("                   本程序实现Avl树的基本操作。                     \n");  
        printf("|                                                                      |\n");   
        printf("|**********************************************************************|\n");  
        printf("|                        Avl树的基本操作如下：                         |\n");  
        printf("|                           0.创建Avl树                                |\n");  
        printf("|                           1.查找                                     |\n");  
        printf("|                           2.插入                                     |\n");  
        printf("|                           3.删除                                     |\n");  
        printf("|                           4.将Avl树遍历                              |\n");  
        printf("|**********************************************************************|\n");   
    
    while(flag){  
            
        printf("|                           请选择功能：                               |\n");   
            
        scanf("%d", &i);     
                                //输入需要选择的功能   
        switch(i){  
            case 0:  
                printf("请输入Avl树的根结点（0代表NULL）:");  
                T = CreateTree();  
                break;   
                    
            case 1:  
                if(T){  
                    printf("请输入要查找的元素：");  
                    scanf("%d", &Element);   
                    if( Find(Element, T))  
                        printf("该元素存在！\n");  
                    else  
                        printf("该元素不存在！\n");  
                }else  
                    printf("       Avl树为空！\n");  
                break;     
                    
            case 2:  
                if(T){  
                    printf("请输入要插入的元素：");  
                    scanf("%d", &Element);   
                    T = Insert(Element, T);   
                }else  
                    printf("       Avl树为空！\n");  
                break;    
                        
            case 3:  
                if(T){  
                    printf("请输入要删除的元素：");  
                    scanf("%d", &Element);   
                    T = Delete(Element, T);   
                }else  
                    printf("       Avl树为空！\n");  
                break;    
            case 4:  
                if(T){  
                    printf("(先序)遍历的结果为：");  
                    PreOrder_1(T);  
                    printf("\n");   
                }else  
                    printf("       Avl树为空！\n");  
                break;    
                        
            default:  
                flag = 0;  
                printf("程序运行结束，按任意键退出！\n");   
        }    
            
    }  
    return 0;  
}   
    
    
    
//Avl树的函数   
AvlTree CreateTree()                                  //创建Avl树   
{  
    ElementType ch;  
    AvlTree T;   
        
    scanf("\n%d", &ch);  
    if(ch == 0)  
        T = NULL;  
    else{  
        if(!(T = (AvlTree)malloc(sizeof(AvlNode))))  
            exit(-1);  
        T->Element  = ch;  
        printf("%d的左儿子为：", T->Element );   
        T->Left = CreateTree();   
        printf("%d的右儿子为：", T->Element );   
        T->Right = CreateTree();  
    }     
    return T;   
}  
    
Position Find(ElementType Element, AvlTree T)                //Avl树的查找   
{  
    if(T == NULL)  
        return NULL;  
    if(Element < T->Element)         //向左找   
        return Find(Element, T->Left);  
    else if(Element > T->Element)    //向右找   
        return Find(Element, T->Right);  
    else  
    return T;             
}  
    
Position FindMax(AvlTree T)                            //找最大值（非递归）   
{  
    if(T != NULL){  
        while(T->Right != NULL )    //一直向右找   
            T = T->Right;          
    }    
    return T;      
}   
    
Position FindMin(AvlTree T)                            //找最小值（非递归）   
{  
    if(T != NULL){                 //一直向左找   
        while(T->Left != NULL )  
            T = T->Left;       
    }       
    return T;      
}   
    
AvlTree Insert(ElementType Element, AvlTree T)         //插入元素到AVL树中   
{  
    if(T == NULL){                    //如果是空树，则初始化之   
        if(!(T = (AvlTree)malloc(sizeof(AvlNode))))  
            exit(-1);  
        else{  
            T->Element = Element;  
            T->Height = 0;  
            T->Left = T->Right = NULL;  
        }  
    }else if(Element < T->Element ){  //向左找   
        T->Left = Insert(Element, T->Left);  
        if(Height(T->Left ) - Height(T->Right ) == 2){  //破坏了Avl树的平衡   
            if(Element < T->Left->Element )  
                T = LeftLeftRotate(T); //左左单旋 
            else   
                T = LeftRightRotate(T);
         } //左右双旋  （先执行逆时针，再执行顺时针，一共旋转2次）   
    }else if(Element > T->Element ){  
        T->Right = Insert(Element, T->Right);  
        if(Height(T->Right ) - Height(T->Left ) == 2){  
            if(Element > T->Right->Element )  
                T = RightRightRotate(T); //右右单旋   
            else   
                T = RightLeftRotate(T); //右左双旋       
        }
    }  
        
    T->Height = Height(T);  //平衡后新树的高度   
    return T;  
        
}  
AvlTree Delete(ElementType Element, AvlTree T)               //删除元素 （与搜索二叉树的删除类似）   
{  
    Position TmpCell;  
    if(T == NULL)                //空树   
        printf("没找到该元素，无法删除！\n");   
    else if(Element < T->Element)  
        T->Left = Delete(Element, T->Left);  
    else if(Element > T->Element)  
        T->Right = Delete(Element, T->Right);  
    else if(T->Left && T->Right){ //要删除的树左右都有儿子   
        TmpCell = FindMin(T->Right);   //用该结点右儿子上最小结点替换该结点，然后与只有一个儿子的操作方法相同   
        T->Element = TmpCell->Element;  
        T->Right = Delete(T->Element, T->Right);  
    }else{  
        TmpCell = T;        //要删除的结点只有一个儿子   
        if(T->Left == NULL)  
            T = T->Right;  
        else if(T->Right == NULL)  
            T = T->Left;  
        free(TmpCell);            
    }  
    return T;  
}     
    
void PreOrder_1(AvlTree T)                           //先序遍历（递归）   
{  
    if(T){  
        
        printf("%d  ", T->Element);  
        PreOrder_1(T->Left);  
        PreOrder_1(T->Right);  
    }  
}   
    
int Height(AvlTree T)                               //返回的高   
{  
if(T == NULL)  
    return 0;  
else  
    return 1 + Max(Height(T->Left ), Height(T->Right ));      
}   

int Max(ElementType A, ElementType B)                //比较树高  
{  
if(A > B)  
    return A;  
else  
    return B;      
}   
    
Position LeftLeftRotate(Position K2)           //左左单旋(又叫右单旋 顺时针)   
{  
    Position K1;  
        
    K1 = K2->Left ;  
    K2->Left = K1->Right ;  
    K1->Right = K2;  
        
    K2->Height = Max(Height(K2->Left ), Height(K2->Right ));  
    K1->Height = Max(Height(K1->Left ), Height(K1->Right ));  
        
    return K1;  
}   
    
Position RightRightRotate(Position K2)          //右右单旋(又叫左单旋 逆时针)
{  
    Position K1;  
        
    K1 = K2->Right ;  
    K2->Right = K1->Left ;  
    K1->Left = K2;  
        
    K2->Height = Max(Height(K2->Left ), Height(K2->Right ));  
    K1->Height = Max(Height(K1->Left ), Height(K1->Right ));  
        
    return K1;  
    
}   
    
Position LeftRightRotate(Position K3)          //左右双旋   
{  
    K3->Left = RightRightRotate(K3->Left );  
        
    return LeftLeftRotate(K3);  
        
    
}   
    
Position RightLeftRotate(Position K3)         //右左双旋  
{  
    K3->Right = LeftLeftRotate(K3->Right );  
        
    return RightRightRotate(K3);  
    
}   


