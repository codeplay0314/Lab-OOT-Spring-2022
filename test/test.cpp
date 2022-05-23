#include "draw.h"
#include <io.h>
#include <cstdio>
#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

void getFileNames(string path, vector<string>& files);
bool endWith(const string&, const string&);

int main() {
    vector<string> files;
    getFileNames(".", files);

    sort(files.begin(), files.end());
    for (int i = 0, size = files.size() - 1; i < size; i++) {
        // Check Test Files
        string in_file = files[i];
        string out_file = files[i + 1];
        int n = in_file.size(), m = out_file.size();
        if (!endWith(in_file, ".txt") || !endWith(out_file, ".txt")) continue;
        if (!endWith(out_file.substr(0, m - 4), "_result")) continue;
        if (in_file.substr(0, n - 4) != out_file.substr(0, m - 11)) continue;
        int gray = 0;
        if (endWith(in_file.substr(0, n - 4), "-g2")) gray = 2;
        else if (endWith(in_file.substr(0, n - 4), "-g256")) gray = 256;
        else continue;
        
        // Set Parameters
        string cmp_file = "tmp.txt";
        FILE* tmp = freopen(cmp_file.c_str(), "w", stdout);
        int argc = 4;
        const char* argv[4] = {"draw", "-g", to_string(gray).c_str(), in_file.c_str()};
        run(argc, (char**)argv);
        fclose(tmp);

        // Compare Results
        ifstream op;
        string str1, str2;
        op.open(out_file);
        while(!op.eof()) str1 += op.get();
        op.close();
        op.open(cmp_file);
        while(!op.eof()) str2 += op.get();
        op.close();
        remove(cmp_file.c_str());
        if (str1 != str2) {
            FILE* fail_file = freopen("fail.log", "w", stdout);
            cout << argv[0] << " "  << argv[1] << " " << argv[2] << " " << argv[3] << " " << endl;
            cout << "------- Your Output of " << in_file <<" -------" << endl;
            cout << str2 << endl;
            cout << "------- Standard Output -------" << endl;
            cout << str1 << endl;
            fclose(fail_file);
            return 0;
        }
    }

    fclose(stdout);
    fprintf(stderr, "OK");
    return 0;
}

bool endWith(const string& str, const string& end) {
    int n = str.length(), m = end.length();
    if (n < m) return false;
    for (int i = 0; i < m; i++) {
        if (str[n - m + i] != end[i]) return false;
    }
    return true;
}

void getFileNames(string path, vector<string>& files) {
    intptr_t hFile = 0;
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFileNames(p.assign(path).append("\\").append(fileinfo.name), files);
            } else {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}