#include <comparator/comparator.h>

// Custom Comparator to sort the array in increasing order
bool customComparator(string a, string b) {
    // Breaking into the octets
    vector<string> octetsA;
    vector<string> octetsB;

    string octet = "";
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] == '.') octetsA.push_back(octet), octet = "";
        else octet += a[i];
    }
    octetsA.push_back(octet);
    //
    octet = "";
    for (size_t i = 0; i < b.size(); i++) {
        if (b[i] == '.') octetsB.push_back(octet), octet = "";
        else octet += b[i];
    }
    octetsB.push_back(octet);

    // Condition if the IP Address is same then return false
    if (octetsA == octetsB) {
        return false;
    }

    // Compare the octets and return the result
    for (int i = 0; i < 4; i++) {
        if (std::stoi(octetsA[i]) < std::stoi(octetsB[i])) {
            return false;
        } else if (std::stoi(octetsA[i]) > std::stoi(octetsB[i])) {
            return true;
        }
    }
    return false;
}

// Function to sort the IP Addresses
vector<string> sortIPAddress(vector<string> arr) {
    // Sort the Array using Custom Comparator
    sort(arr.begin(), arr.end(), customComparator);
    return arr;
}
