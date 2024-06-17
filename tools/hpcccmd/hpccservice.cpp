#include "hpccservice.hpp"
#include "jstring.hpp"
#include <cstring>
#include <iostream>
#include <string>
#include "httpclient.hpp"

using namespace std;

hpccService::hpccService(int argc, const char* argv[], const char* formArgs, const char* resType, const char* reqType){

    string url = "http://127.0.0.1:8010/";
    url.append(argv[1]);
    url += '/';
    url.append(argv[2]);
    url.append(resType);


    const char * c_url = url.c_str();
    cout << url << endl;
    


    StringBuffer req,res;
    req.append(formArgs);
    cout << req << endl;    
    
    Owned<IHttpClientContext> httpctx = getHttpClientContext();
    Owned <IHttpClient> httpclient = httpctx->createHttpClient(NULL, c_url);

    if(strcmp(reqType, "json")==0)
    {
        httpclient->sendRequest("POST","application/json",req,res);
    }
    else if(strcmp(reqType, "form")==0)
    {
        httpclient->sendRequest("POST","application/x-www-form-urlencoded",req,res);
    }
    
    
    cout << res << endl;


    // cout << argv[1] << argv[2] << endl;
    
}