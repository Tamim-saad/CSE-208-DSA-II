#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double

struct Node
{
    ll val;
    Node* left;
    Node* right;
    ll height;

    Node(ll v)
    {
        this->val = v;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};


struct AVL_tree
{
    Node* root;
    string str="",s="";

    ll get_height(Node* node)
    {
        if(node==nullptr) return 0;
        else return node->height;
    }

    bool Find_Node(Node* node, ll v)
    {
        if(node==nullptr) return false;

        if(node->val==v)  return true;

        if(v<node->val) return Find_Node(node->left, v);
        else return Find_Node(node->right, v);
    }


    Node* AntiClockWise_rotation(Node* A)
    {
        Node* B=A->right;
        Node* BL=B->left;

        B->left=A;
        A->right=BL;

        A->height=1+max(get_height(A->left),get_height(A->right));
        B->height=1+max(get_height(B->left),get_height(B->right));

        return B;
    }

    Node* ClockWise_rotation(Node* A)
    {
        Node* B=A->left;
        Node* BR=B->right;

        B->right=A;
        A->left=BR;

        A->height=1+max(get_height(A->left),get_height(A->right));
        B->height=1+max(get_height(B->left),get_height(B->right));

        return B;
    }


    Node* Insert(Node* node,ll v)
    {
        if(node==nullptr) return new Node(v);

        else if(v<node->val) node->left=Insert(node->left,v);
        else if(v>node->val) node->right=Insert(node->right,v);
        else return node;

        if (node == nullptr)
            return node;


        node->height=1+max(get_height(node->left),get_height(node->right));
        ll bf=get_height( node->left)-get_height( node->right);

        if(bf<-1)
        {
            if(v>node->right->val)
                return AntiClockWise_rotation(node);
            else  if(v<node->right->val)
            {
                node->right=ClockWise_rotation(node->right);
                return AntiClockWise_rotation(node);
            }
        }
        if(bf>1)
        {
            if(v<node->left->val)
                return ClockWise_rotation(node);
            else  if(v>node->left->val)
            {
                node->left=AntiClockWise_rotation(node->left);
                return ClockWise_rotation(node);
            }
        }

        return node;
    }

    Node* Delete(Node* node, ll v)
    {
        if(node==nullptr) return node;

        else if(v < node->val) node->left = Delete(node->left, v);
        else if(v > node->val) node->right = Delete(node->right, v);
        else
        {
            if(node->left==nullptr && node->right==nullptr)
                return nullptr;
            else if(node->left==nullptr && node->right!=nullptr)
                return node->right;
            else if(node->left!=nullptr && node->right==nullptr)
                return node->left;
            else
            {
                Node* temp=node->right;
                while (temp->left!=nullptr)
                {
                    temp=temp->left;
                }
                node->val=temp->val;
                node->right=Delete(node->right,temp->val);
            }
        }

       if (node == nullptr)
               return node;


        node->height=1+max(get_height(node->left),get_height(node->right));
        ll bf=get_height(node->left)-get_height(node->right);

        if(bf < -1)
        {
            if(v > node->right->val)
                return AntiClockWise_rotation(node);
            else  if(v < node->right->val)
            {
                node->right = ClockWise_rotation(node->right);
                return AntiClockWise_rotation(node);
            }
        }
        if(bf > 1)
        {
            if(v < node->left->val)
                return ClockWise_rotation(node);
            else  if(v > node->left->val)
            {
                node->left = AntiClockWise_rotation(node->left);
                return ClockWise_rotation(node);
            }
        }

        return node;
    }

    void in_order(Node* node,ofstream &outpt)
    {

        if(node==nullptr) return;

        in_order(node->left,outpt);
        cout<<node->val;
        outpt<<node->val;
        in_order(node->right,outpt);
    }

    void recursive_print(Node* node,ofstream &outpt)
    {
        if(node->left==nullptr && node->right==nullptr)
        {
            cout<<node->val;
            outpt<<node->val;
        }
        else
        {
            cout<<node->val;
            outpt<<node->val;

            cout<<"(";
            outpt<<"(";
            if(node->left!=nullptr) recursive_print(node->left,outpt);

            cout<<",";
            outpt<<",";

            if(node->right!=nullptr) recursive_print(node->right,outpt);
            cout<<")";
            outpt<<")";
        }
    }
};



int main()
{
    ll para;
    string s,choice;
    AVL_tree tree;
    Node *node;
    ld ins_time=0.0,del_time=0.0,src_time=0.0,trav_time=0.0;


    tree.root=nullptr;
    //-----------------------------------------------

    ifstream inpt("tree_input.txt");
    ofstream outpt("tree_output.txt");

    if(!inpt)
    {
        cout<<"Could not open the Input File";
        return 0;
    }

    //-----------------------------------------------
    while(!inpt.eof())
    {
        inpt >> choice;

        if(choice=="I")
        {
            inpt >> para;

            const clock_t time = clock();
            tree.root=tree.Insert(tree.root, para);
            ins_time+= double(clock()-time)/CLOCKS_PER_SEC;

            tree.str="";
            if(tree.root!=nullptr) tree.recursive_print(tree.root,outpt);
            cout<<endl;
            outpt<<endl;


        }
        else if(choice=="D")
        {
            inpt >> para;

            const clock_t time = clock();
            if(tree.Find_Node(tree.root, para)) tree.root=tree.Delete(tree.root, para);
            else continue;
            del_time+= double(clock()-time)/CLOCKS_PER_SEC;

            tree.str="";
            if(tree.root!=nullptr) tree.recursive_print(tree.root,outpt);
            cout<<endl;
            outpt<<endl;

        }
        else if(choice=="F")
        {
            inpt >> para;

            const clock_t time = clock();
            if(tree.Find_Node(tree.root, para)) s="found";
            else s="not found";
            src_time+= double(clock()-time)/CLOCKS_PER_SEC;

            cout << s << endl;
            outpt << s << endl;

        }
        else if(choice=="T")
        {
            tree.str="";

            const clock_t time = clock();
            if(tree.root!=nullptr) tree.in_order(tree.root,outpt);
            trav_time+= float(clock()-time)/CLOCKS_PER_SEC;

            cout<<endl;
            outpt<<endl;
        }
    }

    cout<<"operation time(ms)"<<endl;
    cout<<"insert "<<fixed<<setprecision(8)<<(ld)ins_time<<endl;
    cout<<"delete "<<fixed<<setprecision(8)<<(ld)del_time<<endl;
    cout<<"search "<<fixed<<setprecision(8)<<(ld)src_time<<endl;
    cout<<"trav "  <<fixed<<setprecision(8)<<(ld)trav_time<<endl;
    cout<<"total " <<fixed<<setprecision(8)<<(ld)(ins_time+del_time+src_time+trav_time)<<endl;


    outpt.close();
    inpt.close();
    return 0;
}
