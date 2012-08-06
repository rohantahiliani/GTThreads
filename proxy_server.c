#include "lfu.h"

static size_t write_data(void *buffer, size_t size, 
                         size_t nmemb, void *userp) {
	struct wd_in *wdi = userp;
	wdi->data = realloc(wdi->data, wdi->len + (size*nmemb));
	memcpy(wdi->data + wdi->len, buffer, size * nmemb);
	wdi->len+=size*nmemb;
	return size * nmemb;
}

void copy_result(wd_in *src, wd_in *dest){
	dest->data=src->data;
	dest->len=src->len;
}

void cache_insert(char *u, wd_in *result){
	int a,b;
	a=b=strlen(u)%CACHE_SIZE;
	if(cur_size+result->len >= MAX_CACHE){
		
	}
	if(n[a].count!=0) do{a=(a+1)%CACHE_SIZE;}while(n[a].count!=0 && a!=b); 
	n[a].count=1;
	cur_size+=result->len;
	strcpy(n[a].url,u);
	n[a].index=w_index;
	w[w_index].data=malloc(result->len);
	copy_result(result,&w[w_index++]);
	printf("%s %d %d\nPrinted\n",n[a].url,w_index-1,w[w_index-1].len);fflush(stdout);
}

int cache_find(char *u, wd_in *result){
	int a;
	a=strlen(u)%CACHE_SIZE;
	if(strcmp(n[a].url,u)!=0) do{a=(a+1)%CACHE_SIZE;}while(n[a].count!=0 && strcmp(n[a].url,u)!=0); 
	if(n[a].count==0) return 0;
	n[a].count++;
	copy_result(&w[n[a].index],result);
	printf("%s CACHE HIT at %d\n",u,a);fflush(stdout);
	return 1;
}

bool_t curl_op(char **arg, wd_in *result){
	CURL *curl;
	CURLcode res;
	wd_in wdi;
	char *url = arg[0];
	memset(&wdi, 0, sizeof(wdi));
	curl = curl_easy_init();
	if(NULL != curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &wdi);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		copy_result(&wdi,result);
		cache_insert(url, &wdi);
		return 1;
	}
	else {
		fprintf(stderr, "Error: could not get CURL handle.\n");
		return 0;
	}
}

bool_t
fetchpage_1_svc(char **argp, wd_in *result, struct svc_req *rqstp)
{
	static bool_t retval;
	memset(result,0,sizeof(*result));
	if(!(retval=cache_find(argp[0],result))) retval=curl_op(argp,result);
	return retval;
}

int
proxyserver_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	/*xdr_free (xdr_result, result);*/

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
