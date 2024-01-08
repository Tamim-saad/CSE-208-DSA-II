#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ul;

vector<int>prime_vector;

int prime_nums_generator(int num)
{
    num=2*num;
    prime_vector.clear();
    vector<int>v;
    for(int i=0;i<=num;i++)
    {
        v.push_back(i);
    }
    //cout<<v.size()<<"size"<<endl;
    int i=2;
    while(i<=num)
    {
        i+=2;
        if(i<=num)
            v[i]=0;
    }
    i=3;
    while(i<=num/2)
    {
        int j=i;
        while(j<=num)
        {
            j+=i;
            if(j<=num)
                v[j]=0;
            //cout<<"yes"<<endl;
        }
        i+=2;
        //cout<<i<<" "<<num/2<<endl;
    }
    //cout<<"hel"<<endl;
    for(int i=2;i<=num;i++)
    {
        if(v[i]!=0){
            prime_vector.push_back(v[i]);
        }
    }
    //cout<<"nmj"<<endl;
    /*for(int k=0;k<prime_vector.size();k++)
    {
        cout<<prime_vector[k]<<" ";
    }
    cout<<endl;*/
}

int nearest_prime_number(int n)
{
    int nearest_prime;
    for(int i=0;i<prime_vector.size();i++)
    {
        if(prime_vector[i]>n)
        {
            nearest_prime=prime_vector[i];
            break;
        }
    }
    return nearest_prime;
}

string random_string_generator()
{
    string total_letter="abcdefghijklmnopqrstuvwxyz";
    string new_word=" ";
    int len=5+rand()%5;
    for(int i=0;i<len;i++)
    {
        int pos=rand()%26;
        new_word+=total_letter[pos];
        random_shuffle(total_letter.begin(),total_letter.end());
    }
    //cout<<new_word<<endl;
    return new_word;
}

 ul hashfunction1(string word)
{
    int multiplier=31;
    ul m=1e9+9;
    ul Hash=0;
    ul multiplier_pow=1;
    for(int i=0;i<word.length();i++)
    {
        Hash=(Hash+(word[i]-'a'+1)*multiplier_pow)%m;
        multiplier_pow=(multiplier_pow*multiplier)%m;
    }
    return Hash;
}

ul hashfunction2(string word)
{
   ul Hash = 0;
   ul m=1e9+9;
    for(int i = 0;i<word.size(); i++) {
        Hash = 31 *Hash +word[i];
        Hash=Hash%m;
    }
    return Hash;
}

ul hashfunction3(string word)
{
    ul Hash=0;
    ul m=1e9+9;
    for(int i=1;i<=word.length();i++)
    {
        Hash+=(i*word[i]*2+2*i);
        Hash=Hash%m;
    }
    return Hash;
}

class Node
{
    public:
        string key;
        int val;
};

class separate_chaining_hashing
{
    int tot_size;
    int collison1=0;
    int collison2=0;
    int prob1=0;
    int prob2=0;
    float avg_prob1;
    float avg_prob2;
    vector<string>raw_words;
    vector<vector<Node>>hash_vector;
    int value=1;
    public:
    separate_chaining_hashing(int n)
    {
        tot_size=n;
        prime_nums_generator(n);
        tot_size=nearest_prime_number(n);
               int inserted_unique_words=0;
        while(inserted_unique_words<10000)
        {
            string word=random_string_generator();
            int isin=0;
            for(int k=0;k<raw_words.size();k++)
            {
                if(word==raw_words[k])
                {
                    isin=1;
                    break;
                }
            }
            if(isin==0)
            {
                raw_words.push_back(word);
                inserted_unique_words++;
            }
        }
        //cout<<raw_words.size();
    }

    void initialize_hash_vector()
    {
        for(int i=0;i<tot_size;i++)
        {
            vector<Node>hv;
            Node nod;
            nod.key="A";
            nod.val=-1;
            hv.push_back(nod);
            hash_vector.push_back(hv);
        }
    }

    void seperate_chaining_hashing_insert_controller(int hashfunction)
    {
        hash_vector.clear();
        value=1;
        initialize_hash_vector();
        for(int k=0;k<10000;k++)
        {
            insert(raw_words[k],hashfunction);
        }
    }

    void insert(string word,int hashfunction)
    {
        ul hashpos;
        //cout<<1<<endl;
        if(hashfunction==1)
        {
             hashpos=hashfunction1(word);
             hashpos=hashpos%tot_size;
             //cout<<word<<" "<< hashpos<<endl;
        }
        else if(hashfunction==2)
        {
            hashpos=hashfunction2(word);
            hashpos=hashpos%tot_size;
        }
        int hasfind=0;
        if(hash_vector[hashpos][0].key=="A" && hash_vector[hashpos][0].val==-1)
        {
            hash_vector[hashpos][0].key=word;
            hash_vector[hashpos][0].val=value;
            value++;
        }
        else
        {
            for(int i=0;i<hash_vector[hashpos].size();i++)
            {
                if(hash_vector[hashpos][i].key==word)
                {
                    hasfind=1;
                    break;
                }
                if(hashfunction==1)collison1++;
                if(hashfunction==2)collison2++;    
            }
            if(hasfind==0)
            {
                Node nod;
                nod.key=word;
                nod.val=value;
                value++;
                hash_vector[hashpos].push_back(nod);
            }
        }
    }

    void separate_chaining_hashing_find_controller(int hashfunction)
    {
        int findnum=1000;
        for(int k=0;k<findnum;k++)
        {
            int findword_index=rand()%10000;
            int a=Find(raw_words[findword_index],hashfunction);
        }
        if(hashfunction==1)
        {
            avg_prob1=(float)prob1/findnum;
        }
        if(hashfunction==2)
        {
            avg_prob2=(float)prob2/findnum;
        }
    }

    int Find(string word,int hashfunction)
    {
        int hashpos;
        if(hashfunction==1)
        {
            hashpos=hashfunction1(word);
            hashpos=hashpos%tot_size;
        }
        else if(hashfunction==2)
        {
            hashpos=hashfunction2(word);
            hashpos=hashpos%tot_size;
        }
        for(int i=0;i<hash_vector.size();i++)
        {
            if(hashfunction==1)prob1++;
            else if(hashfunction==2)prob2++;

            if(hash_vector[hashpos][i].key==word)
            {
                return hash_vector[hashpos][i].val;
            }
        }
        return -1;
    }

    int Delete(string word,int hashfunction)
    {
        int hashpos;
        if(hashfunction==1)
        {
            hashpos=hashfunction1(word);
            hashpos=hashpos%tot_size;
        }
        else if(hashfunction==2)
        {
            hashpos=hashfunction2(word);
            hashpos=hashpos%tot_size;
        }
        int hasfound=0;
        for(int i=0;i<hash_vector[hashpos].size();i++)
        {
            if(hash_vector[hashpos][i].key==word)
            {
                hash_vector[hashpos][i].key="A";
                hash_vector[hashpos][i].val=-1;
                hasfound=1;
                break;
            }
        }
        if(hasfound==1)return 1;
        else if(hasfound==0) return -1;
    }

    void show_collision1()
    {
        cout<<collison1<<endl;
    }
    void show_collision2()
    {
        cout<<collison2<<endl;
    }
    void show_avg_prob1()
    {
        cout<<avg_prob1<<endl;
    }
    void show_avg_prob2()
    {
        cout<<avg_prob2<<endl;
    }
};

class Double_Hashing
{
    vector<Node>hash_vector;
    vector<string>raw_words;
    int collison1=0;
    int collison2=0;
    int prob1=0;
    int prob2=0;
    float avg_prob1;
    float avg_prob2;
    int value=1;
    int tot_size;
    string last_word;
    int placelastword=0;
    int curr_function=0;
    int first_total_size;
    public:
    Double_Hashing(int n)
    {
        tot_size=n;
        prime_nums_generator(n);
        tot_size=nearest_prime_number(n);
        first_total_size=tot_size;
        int inserted_unique_words=0;
        while(inserted_unique_words<10000)
        {
            string word=random_string_generator();
            int isin=0;
            for(int k=0;k<raw_words.size();k++)
            {
                if(word==raw_words[k])
                {
                    isin=1;
                    break;
                }
            }
            if(isin==0)
            {
                raw_words.push_back(word);
                inserted_unique_words++;
            }
        }
        last_word=raw_words[raw_words.size()-1];
    }

    void initialize_hash_vector()
    {
        for(int i=0;i<tot_size;i++)
        {
            Node nod;
            nod.key="A";
            nod.val=-1;
            hash_vector.push_back(nod);
        }
    }

    void Double_Hashing_insert_controller(int hashfunction,int rehashing)
    {
        if(rehashing==1)
        {
            tot_size*=2;
            //cout<<value<<endl;
            prime_nums_generator(tot_size);
            tot_size=nearest_prime_number(tot_size);
            value=1;
        }
        if(hashfunction!=curr_function)
        {
            placelastword=0;
            value=1;
            tot_size=first_total_size;
            //curr_function=hashfunction;
        }
        curr_function=hashfunction;
        hash_vector.clear();
        initialize_hash_vector();
        for(int k=0;k<10000;k++)
        {
            insert(raw_words[k],hashfunction);
            if(placelastword==1)break;
        }
    }
    
    void insert(string word,int hashfunction)
    {
        if(word==last_word)placelastword=1;
        if(hashfunction==1)
        {
            //cout<<value<<endl;
            int a=hashfunction1(word);
            int b=hashfunction3(word);
            int hasplaced=0;
            for(int i=0;i<tot_size-1;i++)
            {
                int hashpos=a+i*b;
                hashpos=hashpos%tot_size;
                //cout<<hashpos<<endl;
                if(hash_vector[hashpos].key=="A" && hash_vector[hashpos].val==-1)
                {
                    Node nod;
                    nod.val=value;
                    nod.key=word;
                    hash_vector[hashpos]=nod;
                    value++;
                    hasplaced=1;
                    break;
                }
                if(hash_vector[hashpos].key==word)
                {
                    hasplaced=1;
                    break;
                }
                collison1++;
            }
            if((float)value/(float)tot_size>0.7)
               Double_Hashing_insert_controller(1,1);
        }

        else if(hashfunction==2)
        {
            int a=hashfunction2(word);
            int b=hashfunction3(word);
            int hasplaced=0;
            for(int i=0;i<tot_size-1;i++)
            {
                int hashpos=a+i*b;
                hashpos=hashpos%tot_size;
                if(hash_vector[hashpos].key=="A" && hash_vector[hashpos].val==-1)
                {
                    Node nod;
                    nod.val=value;
                    nod.key=word;
                    hash_vector[hashpos]=nod;
                    value++;
                    hasplaced=1;
                    break;
                }
                collison2++;
            }
            if((float)value/(float)tot_size>0.7)
               Double_Hashing_insert_controller(2,1);
        }
    }

    void Double_hashing_find_controller(int hashfunction)
    {
        int findnum=1000;
        for(int k=0;k<findnum;k++)
        {
            int findword_index=rand()%10000;
            int a=Find(raw_words[findword_index],hashfunction);
        }
        if(hashfunction==1)
        {
            avg_prob1=(float)prob1/findnum;
        }
        if(hashfunction==2)
        {
            //cout<<prob2<<"jkn"<<endl;
            avg_prob2=(float)prob2/findnum;
        }
    }

    int Find(string word,int hashfunction)
    {
        if(hashfunction==1)
        {
            int a=hashfunction1(word);
            int b=hashfunction3(word);
            int hasfound=0;
            for(int i=0;i<tot_size-1;i++)
            {
                int hashpos=a+i*b;
                hashpos=hashpos%tot_size;
                prob1++;
                if(hash_vector[hashpos].key==word)
                {
                    hasfound=1;
                    return hash_vector[hashpos].val;
                }
            }
            if(hasfound==0)
            {
                return -1;
            }
        }

        if(hashfunction==2)
        {
            int a=hashfunction2(word);
            int b=hashfunction3(word);
            int hasfound=0;
            for(int i=0;i<tot_size-1;i++)
            {
                int hashpos=a+i*b;
                hashpos=hashpos%tot_size;
                prob2++;
                if(hash_vector[hashpos].key==word)
                {
                    hasfound=1;
                    return hash_vector[hashpos].val;
                }
            }
            if(hasfound==0)
            {
                return -1;
            }
        }
    }

    int Delete(string word,int hashfunction)
    {
        if(hashfunction==1)
        {
            int a=hashfunction1(word);
            int b=hashfunction3(word);
            int hasfound=0;
            for(int i=0;i<hash_vector.size();i++)
            {
                int hashpos=a+i*b;
                hashpos=hashpos%tot_size;
                if(hash_vector[hashpos].key==word)
                {
                    hasfound=1;
                    hash_vector[hashpos].key="A";
                    hash_vector[hashpos].val=-1;
                }
            }
        }

        if(hashfunction==2)
        {
            int a=hashfunction2(word);
            int b=hashfunction3(word);
            int hasfound=0;
            for(int i=0;i<hash_vector.size();i++)
            {
                int hashpos=a+i*b;
                hashpos=hashpos%tot_size;
                if(hash_vector[hashpos].key==word)
                {
                    hasfound=1;
                    hash_vector[hashpos].key="A";
                    hash_vector[hashpos].val=-1;
                }
            }
        }
    }

    void show_collision1()
    {
        cout<<collison1<<endl;
    }
    void show_collision2()
    {
        cout<<collison2<<endl;
    }
    void show_avg_prob1()
    {
        cout<<avg_prob1<<endl;
    }
    void show_avg_prob2()
    {
        cout<<avg_prob2<<endl;
    }

};

class custom_probing
{
    vector<Node>hash_vector;
    vector<string>raw_words;
    int collison1=0;
    int collison2=0;
    int prob1=0;
    int prob2=0;
    float avg_prob1;
    float avg_prob2;
    int value=1;
    int tot_size;
    string last_word;
    int placelastword=0;
    int curr_function=0;
    int first_total_size;
    int c1=2;
    int c2=2;
    public:
    custom_probing(int n)
    {
        tot_size=n;
        prime_nums_generator(n);
        tot_size=nearest_prime_number(n);
        first_total_size=tot_size;
        //cout<<tot_size<<endl;
        int inserted_unique_words=0;
        while(inserted_unique_words<10000)
        {
            string word=random_string_generator();
            int isin=0;
            for(int k=0;k<raw_words.size();k++)
            {
                if(word==raw_words[k])
                {
                    isin=1;
                    break;
                }
            }
            if(isin==0)
            {
                raw_words.push_back(word);
                inserted_unique_words++;
            }
        }
        last_word=raw_words[raw_words.size()-1];
    }

    void initialize_hash_vector()
    {
        for(int i=0;i<tot_size;i++)
        {
            Node nod;
            nod.key="A";
            nod.val=-1;
            hash_vector.push_back(nod);
        }
    }

    void custom_probing_insert_controller(int hashfunction,int rehashing)
    {
        if(rehashing==1)
        {
            tot_size*=2;
            prime_nums_generator(tot_size);
            tot_size=nearest_prime_number(tot_size);
            //cout<<value<<endl;
            value=1;
        }
        if(hashfunction!=curr_function)
        {
            placelastword=0;
            value=1;
            tot_size=first_total_size;
            //curr_function=hashfunction;
        }
        curr_function=hashfunction;
        hash_vector.clear();
        initialize_hash_vector();
        for(int k=0;k<10000;k++)
        {
            insert(raw_words[k],hashfunction);
            if(placelastword==1)break;
        }
    }
    
    void insert(string word,int hashfunction)
    {
        if(word==last_word)placelastword=1;
        if(hashfunction==1)
        {
            //cout<<value<<endl;
            int a=hashfunction1(word);
            int b=hashfunction3(word);
            int hasplaced=0;
            for(int i=0;i<tot_size-1;i++)
            {
                int hashpos=a+i*b*c1+c2*i*i;
                hashpos=hashpos%tot_size;
                //cout<<hashpos<<endl;
                if(hash_vector[hashpos].key=="A" && hash_vector[hashpos].val==-1)
                {
                    Node nod;
                    nod.val=value;
                    nod.key=word;
                    hash_vector[hashpos]=nod;
                    value++;
                    hasplaced=1;
                    break;
                }
                if(hash_vector[hashpos].key==word)
                {
                    hasplaced=1;
                    break;
                }
                collison1++;
            }
            if((float)value/(float)tot_size>0.7)
               custom_probing_insert_controller(1,1);
        }

        else if(hashfunction==2)
        {
            int a=hashfunction2(word);
            int b=hashfunction3(word);
            int hasplaced=0;
            for(int i=0;i<tot_size-1;i++)
            {
                int hashpos=a+i*b*c1+c2*i*i;
                hashpos=hashpos%tot_size;
                if(hash_vector[hashpos].key=="A" && hash_vector[hashpos].val==-1)
                {
                    Node nod;
                    nod.val=value;
                    nod.key=word;
                    hash_vector[hashpos]=nod;
                    value++;
                    hasplaced=1;
                    break;
                }
                collison2++;
            }
            if((float)value/(float)tot_size>0.7)
               custom_probing_insert_controller(2,1);
        }
    }

    void custom_probing_find_controller(int hashfunction)
    {
        int findnum=1000;
        for(int k=0;k<findnum;k++)
        {
            int findword_index=rand()%10000;
            int a=Find(raw_words[findword_index],hashfunction);
        }
        if(hashfunction==1)
        {
            avg_prob1=(float)prob1/(float)findnum;
        }
        if(hashfunction==2)
        {
            //cout<<prob2<<"jkn"<<endl;
            avg_prob2=(float)prob2/(float)findnum;
        }
    }

    int Find(string word,int hashfunction)
    {
        if(hashfunction==1)
        {
            int a=hashfunction1(word);
            int b=hashfunction3(word);
            int hasfound=0;
            for(int i=0;i<tot_size-1;i++)
            {
                int hashpos=a+i*b*c1+c2*i*i;
                hashpos=hashpos%tot_size;
                prob1++;
                if(hash_vector[hashpos].key==word)
                {
                    hasfound=1;
                    return hash_vector[hashpos].val;
                }
            }
            if(hasfound==0)
            {
                return -1;
            }
        }

        if(hashfunction==2)
        {
            int a=hashfunction2(word);
            int b=hashfunction3(word);
            int hasfound=0;
            for(int i=0;i<tot_size-1;i++)
            {
                int hashpos=a+i*b*c1+c2*i*i;
                hashpos=hashpos%tot_size;
                prob2++;
                if(hash_vector[hashpos].key==word)
                {
                    hasfound=1;
                    return hash_vector[hashpos].val;
                }
            }
            if(hasfound==0)
            {
                return -1;
            }
        }
    }

    int Delete(string word,int hashfunction)
    {
        if(hashfunction==1)
        {
            int a=hashfunction1(word);
            int b=hashfunction3(word);
            int hasfound=0;
            for(int i=0;i<hash_vector.size();i++)
            {
                int hashpos=a+i*b*c1+c2*i*i;
                hashpos=hashpos%tot_size;
                if(hash_vector[hashpos].key==word)
                {
                    hasfound=1;
                    hash_vector[hashpos].key="A";
                    hash_vector[hashpos].val=-1;
                }
            }
        }

        if(hashfunction==2)
        {
            int a=hashfunction2(word);
            int b=hashfunction3(word);
            int hasfound=0;
            for(int i=0;i<hash_vector.size();i++)
            {
                int hashpos=a+i*b*c1+c2*i*i;
                hashpos=hashpos%tot_size;
                if(hash_vector[hashpos].key==word)
                {
                    hasfound=1;
                    hash_vector[hashpos].key="A";
                    hash_vector[hashpos].val=-1;
                }
            }
        }
    }

    void show_collision1()
    {
        cout<<collison1<<endl;
    }
    void show_collision2()
    {
        cout<<collison2<<endl;
    }
    void show_avg_prob1()
    {
        cout<<avg_prob1<<endl;
    }
    void show_avg_prob2()
    {
        cout<<avg_prob2<<endl;
    }

};

int main()
{
    srand(2005108);
    separate_chaining_hashing ob1(5000);
    ob1.seperate_chaining_hashing_insert_controller(1);
    ob1.show_collision1();
    ob1.separate_chaining_hashing_find_controller(1);
    ob1.show_avg_prob1();
    ob1.seperate_chaining_hashing_insert_controller(2);
    ob1.show_collision2();
    ob1.separate_chaining_hashing_find_controller(2);
    ob1.show_avg_prob2();
    Double_Hashing ob2(10000);
    ob2.Double_Hashing_insert_controller(1,0);
    ob2.show_collision1();
    ob2.Double_hashing_find_controller(1);
    ob2.show_avg_prob1();
    ob2.Double_Hashing_insert_controller(2,0);
    ob2.show_collision2();
    ob2.Double_hashing_find_controller(2);
    ob2.show_avg_prob2();
    custom_probing ob3(10000);
    ob3.custom_probing_insert_controller(1,0);
    ob3.show_collision1();
    ob3.custom_probing_find_controller(1);
    ob3.show_avg_prob1();
    ob3.custom_probing_insert_controller(2,0);
    ob3.show_collision2();
    ob3.custom_probing_find_controller(2);
    ob3.show_avg_prob2();
}