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

    
    cout << target << endl;
    string url = target;
    url.append(serviceName);
    url += '/';
    url.append(methodName);
    url.append(resType);


    const char * c_url = url.c_str();
    

    int responseCode = -1;
    StringBuffer req,res,status;
    req.append(formArgs);
    
    Owned<IHttpClientContext> httpctx = getHttpClientContext();
    Owned <IHttpClient> httpclient = httpctx->createHttpClient(NULL, c_url);

    if(strcmp(username, "default")!=0 && strcmp(password, "default") !=0)
    {
        httpclient->setUserID(username);
        httpclient->setPassword(password);
    }
    
    

    if(strcmp(reqType, "json")==0)
    {
       responseCode = httpclient->sendRequest("POST","application/json",req,res, status ,true);

    }
    else if(strcmp(reqType, "form")==0)
    {
       responseCode = httpclient->sendRequest("POST","application/x-www-form-urlencoded",req,res, status ,true);
    }
    else if(strcmp(reqType, "xml")==0)
    {
       responseCode = httpclient->sendRequest("POST","text/xml",req,res, status ,true);
    }

    if(responseCode != 0 )
    {
        cout << "Enter a valid esp target" << endl;
        return;
    }

    if(strcmp("401 Unauthorized", status)==0)
    {
        cout << "Unauthorized Request, Enter a valid username and password" << endl;
        return;
    }
    
    
    
    if(strcmp(resType, ".json") == 0)
    {
        auto jsonTree = createPTreeFromJSONString(res);
        StringBuffer jsonRet;
        toJSON(jsonTree, jsonRet);
        cout << jsonRet;
    }
    else if (strcmp(resType, ".xml") == 0) {
        auto xmlTree = createPTreeFromXMLString(res);
        StringBuffer xmlRet;
        toXML(xmlTree, xmlRet);
        cout << xmlRet << endl;
    }
    else {
        cout << "Error Encountered, couldn't parse response type" << endl;
    }


    
}