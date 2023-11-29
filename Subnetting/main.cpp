#include <bits/stdc++.h>
using namespace std;

class IPaddr
{
    public:
    int oct1,oct2,oct3,oct4,subnetMask;
    bool Class;
    IPaddr()
    {
        this->oct1 = 0;
        this->oct2 = 0;
        this->oct3 = 0;
        this->oct4 = 0;
        this->Class = false;
    }
    IPaddr(int oct1,int oct2,int oct3,int oct4,bool flag)
    {
        this->oct1 = oct1;
        this->oct2 = oct2;
        this->oct3 = oct3;
        this->oct4 = oct4;
        this->Class = flag;
    }
    IPaddr operator&(const IPaddr &other) const
    {
        IPaddr result;
        result.oct1=this->oct1 & other.oct1;
        result.oct2=this->oct2 & other.oct2;
        result.oct3=this->oct3 & other.oct3;
        result.oct4=this->oct4 & other.oct4;

        return result;
    }
    friend ostream& operator<<(ostream& os, const IPaddr& ip);
    friend istream& operator>>(istream& is, IPaddr& ip);
};
ostream& operator<<(ostream& os, const IPaddr& ip) {
    if(!ip.Class)
    os << ip.oct1 << "." << ip.oct2 << "." << ip.oct3 << "." << ip.oct4;
    else
    {
        os << ip.oct1 << "." << ip.oct2 << "." << ip.oct3 << "." << ip.oct4<<" subnet mask: "<<ip.subnetMask;
    }
    return os;
}
istream& operator>>(istream& is, IPaddr& ip) {
    char dot;
    is >> ip.oct1 >> dot >> ip.oct2 >> dot >> ip.oct3 >> dot >> ip.oct4;
        char nextChar = is.peek();
    if (nextChar == '/') {
        is.ignore(); 
        is >> ip.subnetMask;
        ip.Class=1;
    } else {
        ip.subnetMask = 0;
        ip.Class=0;
    }

    return is;
}
int countSetBits(int decimalNumber) {
    int count = 0;

    while (decimalNumber > 0) {
        count += decimalNumber & 1;
        decimalNumber >>= 1;
    }

    return count;
}
void subnets(IPaddr ip,int noOfSubnets, int noOfHosts)
    {
        // Classful Addressing
        if(!ip.Class)
        {
            // Class A
            if(ip.oct1>=1 && ip.oct1<=126)
            {
                cout<<"Class A"<<endl;
                int nid=8;
                int hid=24;
                IPaddr subnetMask(255,0,0,0,false);
                IPaddr networkID=ip & subnetMask;
                IPaddr subnetID=networkID;
                int noOfBitsrequired=ceil(log2(noOfSubnets));
                nid+=noOfBitsrequired;
                if(noOfBitsrequired<9)
                {
                    networkID.oct2+=(255-(pow(2,8-noOfBitsrequired)-1));
                }
                else if(noOfBitsrequired>8 && noOfBitsrequired<17)
                {
                    networkID.oct3+=(255-(pow(2,8-noOfBitsrequired)-1)); 
                }
                else if(noOfBitsrequired>16 && noOfBitsrequired<25)
                {
                    networkID.oct4+=(255-(pow(2,8-noOfBitsrequired)-1));
                }
                cout<<"subnetID: "<<networkID<<endl;
                for (int i = 0; i < noOfSubnets; ++i) {
                    IPaddr firstAddr = networkID;
                    firstAddr.oct3 = i * static_cast<int>(pow(2, 8 - noOfBitsrequired));

                    IPaddr lastAddr = networkID;
                    lastAddr.oct3 = (i + 1) * static_cast<int>(pow(2, 8 - noOfBitsrequired)) - 1;
                    lastAddr.oct4=255;

                    cout << "Subnet " << i + 1 << ": " << firstAddr << " - " << lastAddr << endl;
                }
            }
            // Class B
            else if(ip.oct1>=128 && ip.oct1<=191)
            {
                cout<<"Class B"<<endl;
                int nid=16;
                int hid=16;
                IPaddr subnetMask(255,255,0,0,false);
                IPaddr networkID=ip & subnetMask;
                cout<<"networkID: "<<networkID<<endl;
                IPaddr subnetID = networkID;

                int noOfBitsRequired=ceil(log2(noOfSubnets));
                nid+=noOfBitsRequired; 
                if(noOfBitsRequired<9)
                {
                    subnetID.oct3+=(255-(pow(2,8-noOfBitsRequired)-1)); 
                }
                else if(noOfBitsRequired>8 && noOfBitsRequired<17)
                {
                    subnetID.oct4+=(255-(pow(2,8-noOfBitsRequired)-1));
                }
                cout<<"subnetID: "<<subnetID<<endl;     
                for (int i = 0; i < noOfSubnets; ++i) {
                    IPaddr firstAddr = networkID;
                    firstAddr.oct3 = i * static_cast<int>(pow(2, 8 - noOfBitsRequired));

                    IPaddr lastAddr = networkID;
                    lastAddr.oct3 = (i + 1) * static_cast<int>(pow(2, 8 - noOfBitsRequired)) - 1;
                    lastAddr.oct4=255;

                    cout << "Subnet " << i + 1 << ": " << firstAddr << " - " << lastAddr << endl;
                }                    
            }
            // Class C
            else if(ip.oct1>=192 && ip.oct1<=223)
            {
                cout << "Class C" << endl;
                int nid = 24;
                int hid = 8;
                IPaddr subnetMask(255, 255, 255, 0, false);
                IPaddr networkID = ip & subnetMask;
                IPaddr subnetID = networkID;
                int noOfBitsRequired = static_cast<int>(ceil(log2(noOfSubnets)));
                nid += noOfBitsRequired;

                if (noOfBitsRequired < 9) {
                    subnetID.oct4 += (255 - (pow(2, 8 - noOfBitsRequired) - 1));
                }
                cout<<"network ID: " << networkID << endl;
                cout << "subnet ID: " << subnetID << endl;

                for (int i = 0; i < noOfSubnets; ++i) {
                    IPaddr firstAddr = networkID;
                    firstAddr.oct4 = i * static_cast<int>(pow(2, 8 - noOfBitsRequired));

                    IPaddr lastAddr = networkID;
                    lastAddr.oct4 = (i + 1) * static_cast<int>(pow(2, 8 - noOfBitsRequired)) - 1;

                    cout << "Subnet " << i + 1 << ": " << firstAddr << " - " << lastAddr << endl;
                }
    
            }
            // Class D
            else if(ip.oct1>=224 && ip.oct1<=239)
            {
                cout<<"Class D IP addrees, cannot be assigned to Hosts"<<endl;
            }
            // Class E
            else
            {
                cout<<"Class E IP address, reserved for research purposes only"<<endl;
            }
        }
        else
        {
            
        }
    }
vector<string> separateOctets(string addr)
{
    vector<string>octets;
    bool flag=0;
    int pos=addr.find('/');
    string nid;
    if(pos!=string::npos)
    {
        // Classless address
        flag=1;
        nid=addr.substr(pos+1);
    }
    while ((pos = addr.find('.')) != string::npos) {
        octets.push_back(addr.substr(0, pos));
        addr.erase(0, pos + 1);
    }
    if(flag==1)
    {
        int temp=addr.find('/');
        octets.push_back(addr.substr(0,temp));
        addr.erase(0,temp+1);
        octets.push_back(nid);
    }
    else
        octets.push_back(addr);

    return octets;
}
int main()
{
    cout<<"Enter the IPv4 address: ";
    IPaddr ip;
    cin>>ip;
    int s,h;
    IPaddr subnetMask;
    cout<<"Enter number of subnets: ";
    cin>>s;
    subnets(ip,s,h);
    
}