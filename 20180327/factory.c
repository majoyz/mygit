#include "factory.h"

void factory_init(pfac pf,pfunc thread_func,int cap){
	pf->pthid=(pthread_t*)calloc(pf->pthread_num,sizeof(pthread_t));
	pthread_cond_init(&pf->cond,NULL);
	que_init(&pf->que,cap);
	pf->thread_func=thread_func;
}

void factory_start(pfac pf){
	if(!pf->start_flag){
		for(int i=0;i<pf->pthread_num;i++){
			pthread_create(pf->pthid+i,NULL,pf->thread_func,pf);
		}
		pf->start_flag=1;
	}
}
