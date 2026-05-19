#include <iostream>
using namespace std;
struct ptbnode{
    int data;
    ptbnode *kiri;
    ptbnode *kanan;

    //konstruktor
    ptbnode(int value){
        data = value;
        kiri = nullptr;
        kanan = nullptr;
    }
};

void insert(ptbnode *&akar , int value){
    if(akar == nullptr){
        akar = new ptbnode(value);
        return;
    }
    ptbnode *curr = akar;
    while(true){
        if(value < curr -> data){
            if(curr -> kiri == nullptr){
                curr -> kiri = new ptbnode(value);
                return;
            }
            curr = curr ->kiri;
        }else {
            if(curr ->kanan == nullptr){
                curr -> kanan = new ptbnode(value);
                return;
            }
        curr = curr -> kanan;
        }
    }
}

void preorder(ptbnode *akar){
    if(akar == NULL){
        return;
    }cout << akar -> data;

    preorder(akar -> kiri);
    preorder(akar -> kanan);
}

void postorder(ptbnode *akar){
    if(akar == nullptr){
        return;
    }
    postorder(akar -> kiri);
    postorder(akar -> kanan);

    cout << akar->data;
}