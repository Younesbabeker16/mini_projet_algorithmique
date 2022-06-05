#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

struct Gpoint
{
    float x;
    float y;
    Gpoint* next;

};
struct GPnode
{

    Gpoint* a;
    Gpoint* b;
    Gpoint* c;
    float d;
    GPnode* next;
};
GPnode* create_node(Gpoint* a, Gpoint* b, Gpoint* c, float d)
{
    GPnode* q = new GPnode[1];
    q->a = a;
    q->b = b;
    q->c = c;
    q->d = d;
    q->next = NULL;
    return  q;

}
void find_c(Gpoint* signal, Gpoint* a, Gpoint* b, Gpoint*& c, float& d)
{
    int i_a = 0;
    int i_b = 0;
    int i_c = 0;
    float alpha = (a->y - b->y) / (a->x - b->x);
    float beta = a->y - alpha * a->x;
    float max = 0;
    float dist = 0;

    for (int i = 0; i < 9999; i++)
    {
        if (a->x == signal[i].x)
        {
            i_a = i;
            break;
        }
    }

    for (int i = i_a; i <= 9999; i++)
    {
        if (b->x == signal[i].x)
        {
            i_b = i;
            break;
        }

    }
    //cout << i_a << i_b;

    for (int i = i_a + 1; i < i_b; i++)
    {
        d = abs(((alpha * signal[i].x) + beta) - signal[i].y);
        if (d > max)
        {
            max = d;
            i_c = i;
        }
    }
    c = new Gpoint[1];
    *&c->x = signal[i_c].x;
    *&c->y = signal[i_c].y;
}
GPnode* insert_liste(GPnode* l, Gpoint* a, Gpoint* b, Gpoint* c, float d)
{
    GPnode* q = create_node(a, b, c, d);
    GPnode* h = l; //HEAD
    GPnode* p = h;// TMP  
    if (l == NULL)
        return q;
    while (l != NULL)
    {
        if (d >= l->d)
        {
            if (l == h)
            {
                q->next = h;
                h = q;

            }
            else
            {
                p->next = q;
                q->next = l;

            }
            return h;


        }
        else
        {
            p = l;
            l = l->next;
        }
    }
    p->next = q;
    return h;

}
Gpoint* compression(int  m, float eps)
{
    Gpoint* p = NULL;
    Gpoint* signal = new Gpoint[1000];
    for (int i = 0; i < 1000; i++)
    {
        signal[i].x = i;
        signal[i].y = cos(i);

    }
    int cpt = 2;
    Gpoint* a;
    Gpoint* b;
    Gpoint* c;
    float d;
    a = new Gpoint[1];
    b = new Gpoint[1];
    a->x = signal[0].x;
    a->y = signal[0].y;
    b->x = signal[999].x;
    b->y = signal[999].y;
    c = new Gpoint[1];
    find_c(signal, a, b, c, d);
    Gpoint* liste_des_pt = a;
    liste_des_pt->next = b;
    liste_des_pt->next->next = NULL;
   GPnode* liste_seg = NULL;
    liste_seg = insert_liste(liste_seg, a, b, c, d);
    while (cpt < m)
    {
        a = liste_seg->a;
        b = liste_seg->b;
        c = liste_seg->c;
        d = liste_seg->d;


        if (d <= eps)
        {
            break;
        }
        a->next = c;
        c->next = b;

        liste_seg = liste_seg->next;
        p = new Gpoint[1];
        find_c(signal, a, c, p, d);
        //cout << p->x << " ," << p->y << endl; 
        liste_seg = insert_liste(liste_seg, a, c, p, d);
        p = new Gpoint[1];
        find_c(signal, c, b, p, d);
        liste_seg = insert_liste(liste_seg, c, b, p, d);
        cpt++;
    }
    cout << cpt << endl;
    return liste_des_pt;
}

int main()
{
    Gpoint* signal_comp = NULL;
    signal_comp = compression(50, 0.0000001);
    int i = 0;
    while (signal_comp != NULL)
    {
        cout << "( " << signal_comp->x << " ," << signal_comp->y << ")     "<<endl;
        i++;
        if (i == 10)
        {
            cout << endl;
            i = 0;
        }
        signal_comp = signal_comp->next;
    }
    /*fstream file;
    file.open("file.txt", std::fstream::out );
    if (file)
    {
      cout << " file is created \n";
      while (signal_comp != NULL)
      {
        file << signal_comp->x;
        file << "  ";
        file << signal_comp->y << endl;
        signal_comp = signal_comp->next;
      }

    }*/
    return 0;
}
