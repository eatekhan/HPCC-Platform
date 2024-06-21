#include "hpccservice.hpp"
#include "jptree.hpp"
#include "jstring.hpp"
#include <cstring>
#include <iostream>
#include <string>
#include "httpclient.hpp"

using namespace std;

hpccService::hpccService(const char* serviceName, const char* methodName, const char* formArgs, const char* resType, const char* reqType,
 const char* target, const char* username, const char* password){

    
    // string url = "http://127.0.0.1:8010/";
    cout << target << endl;
    string url = target;
    url.append(serviceName);
    url += '/';
    url.append(methodName);
    url.append(resType);


    const char * c_url = url.c_str();
    // cout << url << endl;
    


    StringBuffer req,res;
    req.append(formArgs);
    // cout << req << endl;    
    
    Owned<IHttpClientContext> httpctx = getHttpClientContext();
    Owned <IHttpClient> httpclient = httpctx->createHttpClient(NULL, c_url);

    if(strcmp(username, "default")!=0 && strcmp(password, "default") !=0)
    {
        httpclient->setUserID(username);
        httpclient->setPassword(password);
    }
    
    cout << req << endl;

    if(strcmp(reqType, "json")==0)
    {
        httpclient->sendRequest("POST","application/json",req,res);
    }
    else if(strcmp(reqType, "form")==0)
    {
        httpclient->sendRequest("POST","application/x-www-form-urlencoded",req,res);
    }
    else if(strcmp(reqType, "xml")==0)
    {
        httpclient->sendRequest("POST","text/xml",req,res);
    }
    
    
    // cout << req << endl;
    if(strcmp(resType, ".json") == 0)
    {
        auto jsonTree = createPTreeFromJSONString(res);
        StringBuffer jsonRet;
        toJSON(jsonTree, jsonRet);
        cout << jsonRet;
    }
    else {
        cout << res << endl;
    }


    
}