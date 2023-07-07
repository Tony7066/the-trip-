#include<bits/stdc++.h>
using namespace std;
#include<SDL2\SDL.h>
//MEANING OF COLORS IN REAL TIME VISUALISATION THAT IS SHOWN
//GREEN --> DESTINATION
//BLUE --> CURR POSITION OF THE VEHICLE
//SKY-BLUE --> CURR LOCATION OF THE PASSANGER
//RED --> THE PATH TRAVERSED BY VEHICLE
//WHITE--> ROADS BETWEEN PLACES
// EVERY CORNER REPRESENTS PLACE IN THE CITY


class Triprecord
{
private:
    unordered_map<string,vector<string>>record;//to maintain the record of customers 'email--> {name,phNo,password}'

    unordered_map<string,bool>pass;//verify the password,weather already used or not 'pass-->{T/F}'

    vector<vector<int>>edges;//behaves as connectivity between locations 'U->node1,V->node2,W->distance between two nodes'

    unordered_map<int,pair<int,int>>nodeloc;//represent the coordinates of the location for representing on visualiser 'node->{x,y}'

    unordered_map<int,vector<pair<int,int>>>adj;//adjacency list of the graph 'node->{neighbor,weight}'

    unordered_map<string,vector<string>>driver;//drivers information 'email-->{name,contact No.}'

    unordered_map<int,pair<string,pair<float,int>>>location; //to store the current location of the driver with its mail id,rating no. of ratings;
    //ie 'location-->{email,{name,ContactNo}}'

public:


    // creation of the node/locations ,edges/routes ,adj,map of node locations,driver ,location
    void generatecity()
    {
        // making roads connectivity between places
        edges= {{0,6,11},{0,1,1},{0,3,2},{5,6,10},{5,1,1},{5,7,3},{1,2,2},{3,9,9},{3,2,6},{3,4,5},{2,4,1},{2,8,2},{7,8,7},{8,9,3}};
        //setting location for every node in xy plane
        nodeloc[0]= {150,100};
        nodeloc[1]= {350,50};
        nodeloc[2]= {250,200};
        nodeloc[3]= {450,300};
        nodeloc[4]= {550,100};
        nodeloc[5]= {50,250};
        nodeloc[6]= {650,250};
        nodeloc[7]= {350,450};
        nodeloc[8]= {150,400};
        nodeloc[9]= {550,400};

        //preparing adj list (connectivity of a city or place with other places)
        int n=edges.size();
        for (int i=0; i<n; i++)
        {
            int u=edges[i][0];
            int v=edges[i][1];
            int w=edges[i][2];
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }

        // put in the drivers information
        driver["123@mahesh"]= {"mahesh","93370##34*"} ;//name ,contact no.

        driver["123@malik"]= {"malik","89660##34*"} ;

        driver["123@gajendra"]= {"gajendra","118964##3*"} ;

        driver["123@david"]= {"david","978813##4*"} ;

        driver["123@simon"]= {"simon","911452##4*"} ;

        // initialising driver's location

        location[2]= {"123@mahesh",{0,0}};
        location[4]= {"123@malik",{0,0}};
        location[6]= {"123@gajendra",{0,0}};
        location[8]= {"123@david",{0,0}};
        location[9]= {"123@simon",{0,0}};
    }


    //options to proceet further with the app
    string choseOption()
    {
        cout<<"\t\t Enter 'login' if you already have an account \n\t\t Enter 'signup' if you are new and want to create an account\n";
        string s;
        cin>>s;
        return s;
    }


    //As name suggests creating a new account
    void createAccount()
    {
        string name,mail,password,PhNo;
        cout<<"\n\t\t Enter your Name: ";
        cin>>name;
        cout<<"\n\t\t Enter your contact No.: ";
        cin>>PhNo;
        int flag=1;
        while (1)
        {
            flag=1;
            cout<<"\n\t\t Enter your email id: ";
            cin>>mail;
            if (record.count(mail)!=0)
            {
                flag=0;
                cout<<"\n\t\t This email id is already registered,try with different ID";
            }
            cout<<"\n\t\t Enter a strong password(Not more than 8 letters): ";
            cin>>password;
            if (pass.count(password)!=0)
            {
                flag=0;
                cout<<"\n\t\t This password is used by someone try new password";
            }
            if (flag==1)
                break;
            //for those already having an account
            cout<<"\n\t\t Enter 1 to continue or 0 to abort";
            int a;
            cin>>a;
            if (a==0)
                break;
        }
        if (flag==1)
        {
            record[mail]= {name,PhNo,password};
            pass[password]=true;
        }
        cout<<"\n\t\t Your account has been successfully created";
    }



    //if user have forgotten the password than this function is called can be used;
    void changepassword()
    {

        while(1)
        {
            cout<<"\n\t\t Enter your email address: ";
            string m;
            cin>>m;
            if (record.count(m)==0)
            {
                cout<<"\n\t\t Account does'not exist with this email id try again:";
            }
            else
            {
                cout<<"\n\t\t Enter new password:";
                string p;
                cin>>p;
                pass.erase(record[m][2]);
                pass[p]=true;
                record[m][2]=p;
                break;
            }
        }
    }


    //uses DIJKATRA'S algorithm to find the shortest path between source and any other node along with the path vector to reach there
    //path vector will be used during visualization of the path // travel time graph
    void shortestpath(vector<int>&d,int src,vector<vector<int>>&path)
    {
        //distance ,node
        d[src]=0;
        set<pair<int,int>>s;
        s.insert({0,src});
        while(!s.empty())
        {
            auto t=*(s.begin());
            int nodedis=t.first;
            int node=t.second;
            s.erase(s.begin());
            for(auto nbr:adj[node])
            {
                if (nbr.second+nodedis<d[nbr.first])
                {
                    d[nbr.first]=nbr.second+nodedis;
                    s.insert({d[nbr.first],nbr.first});
                    vector<int>temp=path[node];
                    temp.push_back(nbr.first);
                    path[nbr.first]=temp;
                }
            }

        }
    }


    //this function finds the drivers near u in a sorted manner of time as well the distance
    void nearestdrivers(vector<pair<int,int>>&nd,vector<int>dist)
    {
        for (int i=0; i<10; i++)
        {
            if (location.count(i)!=0)
                nd.push_back({dist[i],i});
        }
        sort(nd.begin(),nd.end());
    }


    //this function helps users to give their feedbacks to driver
    void rate(int cl)
    {
        int n=location[cl].second.second;
        float cr=location[cl].second.first;//current rating
        float gr;//given rating
        cout<<"\n\t\t Share your experience of travel by giving rating out of 5\n\t\t Ignore by entering -1\n";
        cin>>gr;
        if (gr==-1)
            return ;
        cr=(cr*n+gr)/(n+1);
        location[cl].second.second=n+1;
        location[cl].second.first=cr;
    }


    //this function call shows us the real time map and help user to keep track of their journey
    void draw_curr_state(SDL_Renderer * r,vector<vector<int>>&path,int dst,int src,int vehicle,int flag,int cl)
    {
        //drawing the graph on canvas with white color;
        for (auto i:edges)
        {
            int u=i[0];
            int v=i[1];
            int x1=nodeloc[u].first;
            int y1=nodeloc[u].second;
            int x2=nodeloc[v].first;
            int y2=nodeloc[v].second;
            SDL_SetRenderDrawColor(r,255,255,255,255);
            SDL_RenderDrawLine(r,x1,y1,x2,y2);
        }

        vector<int>temp;
        temp=path[cl];
        int n=temp.size();
        //drawing the path that goes from vehicle to customer with red color;
        for (int i=1; i<n; i++)
        {

            int u=temp[i-1];
            int v=temp[i];
            int x1=nodeloc[u].first;
            int y1=nodeloc[u].second;
            int x2=nodeloc[v].first;
            int y2=nodeloc[v].second;
            SDL_SetRenderDrawColor(r,255,0,0,255);
            SDL_RenderDrawLine(r,x1,y1,x2,y2);
        }

        temp=path[dst];
        n=temp.size();
        //drawing the path that goes from customer location to destination with red color;
        for (int i=1; i<n; i++)
        {

            int u=temp[i-1];
            int v=temp[i];
            int x1=nodeloc[u].first;
            int y1=nodeloc[u].second;
            int x2=nodeloc[v].first;
            int y2=nodeloc[v].second;
            SDL_SetRenderDrawColor(r,255,0,0,255);
            SDL_RenderDrawLine(r,x1,y1,x2,y2);
        }

        // highlighting the current positions of vehicle,destination and (user if not picked by driver)
        SDL_SetRenderDrawColor(r,0,255,0,255);
        SDL_Rect rect;
        rect.w=10;
        rect.h=10;
        rect.x=nodeloc[dst].first-5;
        rect.y=nodeloc[dst].second-5;
        SDL_RenderFillRect(r,&rect);

        SDL_SetRenderDrawColor(r,0,0,255,255);
        rect.w=10;
        rect.h=10;
        rect.x=nodeloc[vehicle].first-5;
        rect.y=nodeloc[vehicle].second-5;
        SDL_RenderFillRect(r,&rect);

        //flag==1 represents that costomer is still not picked up by driver;
        if(flag==1)
        {
            SDL_SetRenderDrawColor(r,0,255,255,255);
            rect.w=10;
            rect.h=10;
            rect.x=nodeloc[src].first-5;
            rect.y=nodeloc[src].second-5;
            SDL_RenderFillRect(r,&rect);
        }
        return ;
    }


    //function called to show the path taken and curr locations of vehicle, customer, destination
    void  ShowpathAndLocation(int src,int dst,vector<vector<int>>&path,int cl)
    {
        SDL_Window  *w=nullptr;
        SDL_Renderer *r=nullptr;
        SDL_CreateWindowAndRenderer(1400,1000,0,&w,&r);
        SDL_RenderSetScale(r,2,2);
        vector<int>v1,v2;
        v1=path[dst];
        v2=path[cl];//chosen location->cl
        int n=v2.size();
        for(int i=n-1; i>=0; i--)
        {
            //clear screen ;
            SDL_SetRenderDrawColor(r,0,0,0,255);
            SDL_RenderClear(r);
            //draw curr satte of the graph
            draw_curr_state(r,path,dst,src,v2[i],1,cl);
            //present screen
            SDL_RenderPresent(r);
            //delay;
            SDL_Delay(1000);
        }

        n=v1.size();
        for(int i=0; i<n; i++)
        {
            //clear screen ;
            SDL_SetRenderDrawColor(r,0,0,0,255);
            SDL_RenderClear(r);
            //draw curr satte of the graph
            draw_curr_state(r,path,dst,src,v1[i],0,cl);
            //present screen
            SDL_RenderPresent(r);
            //delay;
            SDL_Delay(1000);
        }
        return ;
    }


    //helps customer to choose driver
    void selectDriver(vector<pair<int,int>>&nd,int dst,vector<int>dist,int src,vector<vector<int>>&path)
    {
        cout<<"\n\n\t\ These are the lists of driver near you...";
        cout<<"\n\n\tName\t\tContact\t\t      Rating\t\t  id\t\t Reach destination in (min)\t  Cost";
        for (int i=0; i<5; i++)
        {
            int d1=nd[i].first;
            int d2=dist[dst];
            int l=nd[i].second;
            float t=1.0*(d1+d2)/2;
            string id=location[l].first;
            float rating=location[l].second.first;
            string name=driver[id][0];
            string no=driver[id][1];
            cout<<"\n\t"<<name<<"\t\t"<<no<<"\t\t"<<rating<<"\t\t"<<id<<"\t\t"<<t<<"\t\t         Rs "<<10*(d1+d2);
        }
        cout<<"\n\n\t\t Chose a driver by just writing his/her id: ";
        string id;
        cin>>id;
        int n,cl;
        for(auto i:location)
        {
            if (i.second.first==id)
            {
                cl=i.first;
            }
        }
        cout<<"\n\t\t Enter 1 to make On-line payment \n\t\t Enter 2 to make cash payment \n\t\t Enter -1 to cancel booking\n\t\t Choosing either 1 or 2 confirms your booking\n";
        cin>>n;
        if (n==-1)
            return ;
        //if on-line than add methods for payment,can give phone no. qr scanner or account details etc;
        for(auto i:location)
        {
            if (i.second.first==id)
            {
                cl=i.first;
            }
        }
        ShowpathAndLocation(src,dst,path,cl);
        rate(cl);
    }


    // starts the booking procedure if user want to book vehicle
    void bookvehicle(string mail)
    {
        cout<<"\n\t\t Enter pickup location: ";
        int src;
        cin>>src;
        cout<<"\n\t\t Enter destination: ";
        int dst;
        cin>>dst;

        //  finding the shortest distance between source and destination;
        vector<int>dist(10,INT_MAX);
        vector<vector<int>>path(10);
        path[src].push_back({src});
        // finding shortest path between source and any node;
        shortestpath(dist,src,path);

        vector<pair<int,int>>nd;//nearest drivers;//dist,current location
        nearestdrivers(nd,dist);
        selectDriver(nd,dst,dist,src,path);
    }


    // checks weather the user is having an account or not,if no account,than tells user to create new account;
    void check()
    {
        string s;
        cout<<"\n\t\t Want to book vehicle (yes/no)?: ";
        cin>>s;
        if (s=="yes")
        {
            string mail;
            cout<<"\n\t\t Enter Your email id: ";
            cin>>mail;
            int c=1;
            while(c<5)
            {
                if(record.count(mail)==0)
                    cout<<"\n\t\t This email id does not exist please try again ,"<<5-c<<" chances remaining: ";
                else
                {
                    break;
                }
                mail="";
                cin>>mail;
                c++;

            }
            if(c==5)
            {
                cout<<"\n\t\t This email id does not exist please try with a new account:\n\n";
                return ;
            }

            while(1)
            {
                cout<<"\n\t\t Enter password: ";
                string p;
                cin>>p;
                if (pass.count(p)==0)
                {
                    cout<<"\n\t Password is wrong";
                    cout<<"\n\t Want to change your password(yes/no): ";
                    string y;
                    cin>>y;
                    if (y=="yes")
                    {
                        changepassword();
                    }
                    else
                    {

                        cout<<"\n\t\t Please try again";
                    }
                }
                else
                {
                    bookvehicle(mail);
                    break;
                }
            }
        }
    }

};


int main(int argc,char *argv[])
{
    Triprecord t;
    t.generatecity();
    while(1)
    {
        cout<<" Enter 1 to open the website \n Enter 0 to close the website \n";
        int n;
        cin>>n;
        if(n==0)
            break;
        string s=t.choseOption();
        if (s=="signup")
        {
            t.createAccount();
        }
        else if (s!="login")
            continue;
        t.check();
    }
    return 0;
}
