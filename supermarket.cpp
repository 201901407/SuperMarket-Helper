#include <bits/stdc++.h>
#define ll long long

using namespace std;

//structure denoting the items
struct item{
    ll prod_id;
    string name;
    double rate;
    ll quantity;
    item *next;
};

//structure denoting the customer data
struct customer_data{
    ll customer_id;
    string customer_name;
    ll points;
    customer_data* nextnode;
};

//class denoting the inventory    
class inventory{
    //hashtable of size 32 denoting the inventory of items
    item table[32];
    protected:
    int hashfunction(ll id)
    {
        return id%32;
    }
    
    void add(ll b, string n, double r, ll q)
    {
        int bucket = hashfunction(b);
        if(table[bucket].prod_id == -1)
        {
            table[bucket].prod_id = b;
            table[bucket].name = n;
            table[bucket].rate = r;
            table[bucket].quantity = q;
            table[bucket].next = NULL;
        }
        else{
            item* temp = new item;
            temp->prod_id = b;
            temp->name = n;
            temp->rate = r;
            temp->quantity = q;
            temp->next = NULL;
            item* count = &(table[bucket]);
            item* count1 = new item;
            count1->prod_id = table[bucket].prod_id;
            count1->name = table[bucket].name;
            count1->rate = r;
            count1->quantity = q;
            count1->next = table[bucket].next;
            if(count->prod_id > b)
            {
                table[bucket].prod_id = b;
                table[bucket].name = n;
                table[bucket].rate = r;
                table[bucket].quantity = q;
                table[bucket].next = count1;
            }
            else{
                item* prev = count;
                int i = 0;
                while(count->prod_id < b && count->next != NULL)
                {
                    if(i!=0)
                    {
                        prev = prev->next;
                    }
                    count = count->next;
                    i++;
                }
                if(count->next == NULL && count->prod_id < b)
                {
                    count->next = temp;
                }
                else{
                    prev->next = temp;
                    (temp)->next = count;
                }
            }
        }
        cout<<"Product added to inventory successfully!\n";
    }
    
    void deletenode(ll d)
    {
        int bucket = hashfunction(d);
        if(table[bucket].prod_id==d)
        {
            if(table[bucket].next != NULL)
            {
                item* count = table[bucket].next;
                table[bucket].prod_id = count->prod_id;
                table[bucket].name = count->name;
                table[bucket].rate = count->rate;
                table[bucket].quantity = count->quantity;
                table[bucket].next = count->next;
                delete count;
            }
            else{
                table[bucket].prod_id = -1;
                table[bucket].name = "NULL";
                table[bucket].rate = -1;
                table[bucket].quantity = -1;
            }
        }
        else{
            item* count = table[bucket].next;
            item* prev = &table[bucket];
            if(count == NULL)
            {
                cout<<"Error! No such product in the inventory.\n";
            }
            else{
                while(count->prod_id != d && count->next != NULL)
                {
                    prev = prev->next;
                    count = count->next;
                }
                if(count->next == NULL)
                {
                    cout<<"Error! No such product in the inventory table.\n";
                }
                else{
                    prev->next = count->next;
                    delete count;
                    cout<<"Product has been deleted successfully.\n";
                }
            }
        }
    }
    
    void update(ll id, string n, double r, ll q)
    {
        int bucket = hashfunction(id);
        if(table[bucket].prod_id == -1)
        {
            cout<<"Error! Product doesn't exist.\n";
        }
        else{
            item* count = table[bucket].next;
            if(table[bucket].prod_id == id)
            {
                table[bucket].name = n;
                table[bucket].rate = r;
                table[bucket].quantity = q;
            }
            else{
                if(count->prod_id == id)
                {
                    count->name = n;
                    count->rate = r;
                    count->quantity = q;
                }
                else{
                while(count->prod_id != id && count->next != NULL)
                {
                    count = count->next;
                }
                if(count->prod_id == id)
                {
                    count->name = n;
                    count->rate = r;
                    count->quantity = q;
                    cout<<"Product details updated successfully!\n";
                }
                if(count->next == NULL && count->prod_id != id)
                {
                    cout<<"Error! Product doesn't exist\n";
                }
                }
            }
        }
    }

    public:
    inventory()
    {
        for(int i = 0;i < 32;i++)
        {
            table[i].prod_id = -1;
            table[i].name = "NULL";
            table[i].rate = -1;
            table[i].quantity = -1;
            table[i].next = NULL;
        }
    }
    
    void update_stock(ll id, ll q)
    {
        int bucket = hashfunction(id);
        if(table[bucket].prod_id == -1)
        {
            cout<<"Error! Product doesn't exist.\n";
        }
        else{
            item* count = table[bucket].next;
            if(table[bucket].prod_id == id)
            {
                table[bucket].quantity = table[bucket].quantity - q;
            }
            else{
                if(count->prod_id == id)
                {
                    count->quantity = count->quantity - q;
                }
                else{
                while(count->prod_id != id && count->next != NULL)
                {
                    count = count->next;
                }
                if(count->prod_id == id)
                {
                    count->quantity = count->quantity + q;
                    cout<<"Stock of the product updated successfully\n";
                }
                if(count->next == NULL && count->prod_id != id)
                {
                    cout<<"Error! Product doesn't exist\n";
                }
                }
            }
        }
    }
    
    item* Get_Product_Info(ll id)
    {
        int bucket = hashfunction(id);
        item* n = new item;
        n->prod_id = -1;
        n->name = "NULL";
        n->rate = -1;
        n->quantity = -1;
        if(table[bucket].prod_id == -1)
        {
            cout<<"Error! Product Not Found\n";
            return n;
        }
        else{
            if(table[bucket].prod_id == id)
            {
                return &table[bucket];
            }
            else{
                item* count = table[bucket].next;
                if(count->prod_id == id)
                {
                    return count;
                }
                else{
                while(count->prod_id != id && count->next != NULL)
                {
                    count = count->next;
                }
                if(count->prod_id == id)
                {
                    return count;
                }
                if(count->next == NULL && count->prod_id != id)
                {
                    cout<<"Error! Product Not Found\n";
                    return n;
                }
                }
            }
        }
    }
}main_inventory;

class Manager:public inventory
{
    ll manager_id;
    ll manager_name;
    public:
    void add_item(ll b,string n, double r, ll q)
    {
        //srand(time(0));
        //ll b = rand()%((ll)1e9+7) + rand();
        add(b,n,r,q);
    }
    void delete_item(ll b)
    {
        deletenode(b);
    }
    void update_item(ll id, string n, double r, ll q)
    {
        update(id,n,r,q);
    }
}administrator;

class customer{
    customer_data customer_table[128]; 
    protected:
    int hashfunction(ll id)
    {
        return id%128;
    }
    void Add_customer(ll id, string n, ll p)
    {
        int bucket = hashfunction(id);
        if(customer_table[bucket].customer_id == -1)
        {
        customer_table[bucket].customer_id = id;
        customer_table[bucket].customer_name = n;
        customer_table[bucket].points = p;
        customer_table[bucket].nextnode = NULL;
        }
        else{
            customer_data* temp = new customer_data;
            temp->customer_id = id;
            temp->customer_name = n;
            temp->points = p;
            temp->nextnode = NULL;
            customer_data* count = &(customer_table[bucket]);
            customer_data* count1 = new customer_data;
            count1->customer_id = customer_table[bucket].customer_id;
            count1->customer_name = customer_table[bucket].customer_name;
            count1->points = p;
            count1->nextnode = customer_table[bucket].nextnode;
            if(count->customer_id > id)
            {
                customer_table[bucket].customer_id = id;
                customer_table[bucket].customer_name = n;
                customer_table[bucket].points = p;
                customer_table[bucket].nextnode = count1;
            }
            else{
                customer_data* prev = count;
                int i = 0;
                while(count->customer_id < id && count->nextnode != NULL)
                {
                    if(i!=0)
                    {
                        prev = prev->nextnode;
                    }
                    count = count->nextnode;
                    i++;
                }
                if(count->nextnode == NULL && count->customer_id < id)
                {
                    count->nextnode = temp;
                }
                else{
                prev->nextnode = temp;
                (temp)->nextnode = count;
                }
            }
        }
        cout<<"Customer details inserted successfully.\n";
    }
    void Update_points(ll id, ll p)
    {
        int bucket = hashfunction(id);
        if(customer_table[bucket].customer_id == -1)
        {
            cout<<"Error! Customer doesn't exist.\n";
        }
        else{
            customer_data* count = customer_table[bucket].nextnode;
            if(customer_table[bucket].customer_id == id)
            {
                customer_table[bucket].points = customer_table[bucket].points + p;
            }
            else{
                if(count->customer_id == id)
                {
                    count->points = count->points + p;
                }
                else{
                while(count->customer_id != id && count->nextnode != NULL)
                {
                    count = count->nextnode;
                }
                if(count->customer_id == id)
                {
                   count->points = count->points + p;
                   cout<<"Points updated successfully.\n";
                }
                if(count->nextnode == NULL && count->customer_id != id)
                {
                    cout<<"Customer doesn't exist\n";
                }
                }
            }
        }
    }
    public:
    customer()
    {
        for(int i = 0;i <128;i++)
        {
            customer_table[i].customer_id = -1;
            customer_table[i].customer_name = "NULL";
            customer_table[i].points = 0;
            customer_table[i].nextnode = NULL;
        }
    }
    int Is_Customer(ll id)
    {
        int bucket = hashfunction(id);
        if(customer_table[bucket].customer_id == -1)
        {
            return -1;
        }
        else{
            if(customer_table[bucket].customer_id == id)
            {
                return 1;
            }
            else{
                customer_data* count = customer_table[bucket].nextnode;
                if(count->customer_id == id)
                {
                    return 1;
                }
                else{
                while(count->customer_id != id && count->nextnode != NULL)
                {
                    count = count->nextnode;
                }
                if(count->customer_id == id)
                {
                    return 1;
                }
                if(count->nextnode == NULL && count->customer_id != id)
                {
                    return -1;
                }
                }
            }
        }
    }
    int get_Points(ll id)
    {
        int bucket = hashfunction(id);
        if(customer_table[bucket].customer_id == -1)
        {
            return -1;
        }
        else{
            if(customer_table[bucket].customer_id == id)
            {
                return customer_table[bucket].points;
            }
            else{
                customer_data* count = customer_table[bucket].nextnode;
                if(count->customer_id == id)
                {
                    return count->points;
                }
                else{
                while(count->customer_id != id && count->nextnode != NULL)
                {
                    count = count->nextnode;
                }
                if(count->customer_id == id)
                {
                    return count->points;
                }
                if(count->nextnode == NULL && count->customer_id != id)
                {
                    return -1;
                }
                }
            }
        }
    }
    customer_data* Get_Customer_Info(ll id)
    {
        int bucket = hashfunction(id);
        customer_data* temp = new customer_data;
        temp->customer_id = -1;
        temp->customer_name = "NULL";
        temp->points = 0;
        temp->nextnode = NULL;
        if(customer_table[bucket].customer_id == -1)
        {
            return temp;
        }
        else{
            if(customer_table[bucket].customer_id == id)
            {
                return &customer_table[bucket];
            }
            else{
                customer_data* count = customer_table[bucket].nextnode;
                if(count->customer_id == id)
                {
                    return count;
                }
                else{
                while(count->customer_id != id && count->nextnode != NULL)
                {
                    count = count->nextnode;
                }
                if(count->customer_id == id)
                {
                    return count;
                }
                if(count->nextnode == NULL && count->customer_id != id)
                {
                    return temp;
                }
                }
            }
        }
    }
};

class billing:public customer
{
    ll transaction_id;
    ll cu_id;
    item* head;
    item* tail;
    ll total;
    public:
    void new_customer(ll cid, string gg)
    {
        int truth = Is_Customer(cid);
        if(truth == -1)
        {
            Add_customer(cid,gg,0);
            cout<<"Customer added successfully!\n";
        }
        srand(time(0));
        transaction_id = rand()%((ll)1e9+7) + rand();
        cu_id = cid;
        head = NULL;
        tail = NULL;
        total = 0;
        if(truth != -1) cout<<"Welcome back to supermarket!\n";
    }
    
    void add_in_bill(item* a, int q)
    {
        item* temp = new item;
        temp->next = NULL;
        temp->quantity = q;
        temp->prod_id = a->prod_id;
        temp->rate = a->rate;
        temp->name = a->name;
        if(head == NULL && tail == NULL)
        {
            head = temp;
            tail = temp;
        }
        else if(head == tail)
        {
            head->next = temp;
            tail = head->next;
            tail->next = NULL;
        }
        else{
            item* curr = head->next;
            while(curr->next != NULL)
            {
                curr = curr->next;
            }
            curr->next = temp;
            tail = curr->next;
        }
        cout<<"Item added successfully in customer's cart!\n";
    }
    
    void delete_in_bill(item* a)
    {
        item* curr = head;
        item* prev = curr;
        if(curr->prod_id == a->prod_id)
        {
            head = curr->next;
            curr->next = NULL;
            delete curr;
        }
        else{
            int i = 0;
            while(curr->prod_id != a->prod_id && curr->next != NULL)
            {
                if(i!=0)
                {
                    prev = prev->next;
                }
                curr = curr->next;
                i++;
            }
            prev->next = curr->next;
            curr->next = NULL;
            delete curr;
        }
        cout<<"Item deleted successfully from customer's cart!\n";
    }
    
    void change_quantity(item* a,ll q)
    {
        item* curr = head;
        if(curr->prod_id == a->prod_id)
        {
            curr->quantity += q;
        }
        else{
            while(curr->prod_id != a->prod_id && curr->next != NULL)
            {
                curr = curr->next;
            }
            if(curr->prod_id == a->prod_id)
            {
                curr->quantity += q;
            }
        }
        cout<<"Item's Quantity changed successfully in customer's cart!\n";
    }
    
    void make_payment()
    {
        cout<<"Transaction ID: "<<transaction_id<<"\n";
        cout<<"Customer ID: "<<cu_id<<"\n";
        cout<<"Product ID\t\t\tProduct Name\t\t\tRate(per pc)\t\t\tQuantity\t\t\tAmount(in Rs.)\n";
        item* curr = head;
        while(curr != NULL)
        {
            cout<<curr->prod_id<<"\t\t\t\t"<<curr->name<<"\t\t\t\t"<<curr->rate<<"\t\t\t\t"<<curr->quantity<<"\t\t\t\t"<<curr->quantity*curr->rate<<"\n";
            total = total + curr->quantity*curr->rate;
            administrator.update_stock(curr->prod_id,curr->quantity);
            curr = curr->next;
        }
        Update_points(cu_id,total/10);
        customer_data* temp;
        temp = Get_Customer_Info(cu_id);
        cout<<"Total Amount to be paid: "<<total<<"\nUpdated points: "<<temp->points<<"\n";
    }
}b;

int main() {
	item* s;
	customer_data* q;
    while(1)
    {
        cout<<"List of available options. Please select the valid option:\n";
        cout<<"1. Add an item to inventory\n";
        cout<<"2. Get information about a particular product from inventory\n";
        cout<<"3. Delete an item from inventory\n";
        cout<<"4. Update an item's information in the inventory\n";
        cout<<"5. Update the stock information of a particular product in the inventory\n";
        cout<<"6. Add a new customer to customer records\n";
        cout<<"7. Add a new product to the customer's cart\n";
        cout<<"8. Change quantity of the product in customer's cart\n";
        cout<<"9. Delete a particular product in customer's cart\n";
        cout<<"10. Display final billing of the customer\n";
        cout<<"11. Display the final points of the customer\n";
        cout<<"12. Get the details of the customer\n";
        cout<<"13. Exit the program\n";
        int choice;
        cin>>choice;
        if(choice == 1)
        {
            ll id,q;
            double rate;
            string s;
            cout<<"Please enter the details of the item to be added: \nID: ";
            cin>>id;
            cout<<"\nName: ";
            cin>>s;
            cout<<"\nRate: ";
            cin>>rate;
            cout<<"\nQuantity: ";
            cin>>q;
            administrator.add_item(id,s,rate,q);
        }
        else if(choice == 2)
        {
            ll id;
            cout<<"Please enter the ID of the product:\n";
            cin>>id;
            item* s1 = administrator.Get_Product_Info(id);
            cout<<"Name of the product: "<<s1->name<<"\nQuantity of the product available in inventory: "<<s1->quantity<<"\nRate of the product: "<<s1->rate<<"\n";
        }
        else if(choice == 3)
        {
            ll id;
            cout<<"Please enter the ID of the product:\n";
            cin>>id;
            administrator.delete_item(id);
        }
        else if(choice == 4)
        {
            ll id,q;
            double rate;
            string s;
            cout<<"Please enter the details of the item to be updated:\nID of the product: ";
            cin>>id;
            cout<<"\nName: ";
            cin>>s;
            cout<<"\nRate: ";
            cin>>rate;
            cout<<"\nQuantity: ";
            cin>>q;
            administrator.update_item(id,s,rate,q);
        }
        else if(choice == 5)
        {
            ll id,q;
            cout<<"Please enter the ID of the product and the quantity to be subtracted/added: ";
            cin>>id>>q;
            administrator.update_stock(id,q);
        }
        else if(choice == 6)
        {
            ll id;
            string s;
            cout<<"Please enter the customer name and ID: ";
            cin>>s>>id;
            //srand(time(0));
            //ll id = rand()%((ll)1e9+7) + rand();
            b.new_customer(id,s);
        }
        else if(choice == 7)
        {
            ll id,q;
            cout<<"Please enter the ID of the product to be inserted in customer's bill and its quantity: ";
            cin>>id>>q;
            s = administrator.Get_Product_Info(id);
            if(s->name == "NULL")
            {
                //cout<<"Product doesn't exist in inventory!\n";
                continue;
            }
            b.add_in_bill(s,q);
        }
        else if(choice == 8)
        {
            ll id,q;
            cout<<"Please enter the ID of the product and the quantity to be subtracted/added: ";
            cin>>id>>q;
            s = administrator.Get_Product_Info(id);
            b.change_quantity(s,q);
        }
        else if(choice == 9)
        {
            ll id;
            cout<<"Please enter the ID of the product:\n";
            cin>>id;
            s = administrator.Get_Product_Info(id);
            b.delete_in_bill(s);
        }
        else if(choice == 10)
        {
            b.make_payment();
        }
        else if(choice == 11)
        {
            ll id;
            cout<<"Please enter the ID of the customer:\n";
            cin>>id;
            b.get_Points(id);
        }
        else if(choice == 12)
        {
            ll id;
            cout<<"Please enter the ID of the customer:\n";
            cin>>id;
            q = b.Get_Customer_Info(id);
            cout<<"Name of the Customer: "<<q->customer_name<<"\nID of the customer: "<<q->customer_id<<"\nPoints of the customer: "<<q->points<<"\n";
        }
        else
        {
            break;
        }
    }
	return 0;
}
