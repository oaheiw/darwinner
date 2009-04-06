///////////////////////////////////////////////////////////
//  WorkerFactory.cpp
//  Implementation of the Class WorkerFactory
//  Created on:      03-ËÄÔÂ-2009 15:42:33
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////
#include "common.h"
#include "WorkerFactory.h"
#include "Worker.h"

WorkerFactory::WorkerFactory(){

}



WorkerFactory::~WorkerFactory(){
	delete m_handler;
}

IActionHandler* WorkerFactory::CreateWorker(){
	if(NULL != m_handler) {
		m_handler = new Worker();
	}
	return  m_handler;
}