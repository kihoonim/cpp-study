//#pragma comment(lib, "Ws2_32.lib")

#include <memory>
#include <grpcpp/grpcpp.h>
#include "../common/server_base.hpp"

#include "basic.pb.h"
#include "basic.grpc.pb.h"

class GrpcServiceImplementation : public basic_package::BasicService::Service {
private:
public:
	grpc::Status BasicUnary(
		grpc::ServerContext* context,
		const basic_package::Request* request,
		basic_package::Reply* reply) override;

 	grpc::Status BasicServerStreaming(
		 grpc::ServerContext* context, 
		 const ::basic_package::Request* request, 
		 grpc::ServerWriter<basic_package::Reply>* writer) override;
   
    grpc::Status BasicClientStreaming(
		grpc::ServerContext* context, 
		grpc::ServerReader<basic_package::Request>* reader, 
		basic_package::Reply* reply) override;

	grpc::Status BasicBidirectionalStreaming(
		grpc::ServerContext* context,
		grpc::ServerReaderWriter<
		basic_package::Reply, 
		basic_package::Request>* stream) override;
};

grpc::Status GrpcServiceImplementation::BasicUnary(
	grpc::ServerContext* context,
	const basic_package::Request* request,
	basic_package::Reply* reply) {

	std::cout << "BasicUnary Called : " << request->value() << std::endl;

	grpc::Status status;

	try {
		if (std::strcmp(request->value().c_str(), "OK") == 0) {
			reply->set_value(request->value());
			return grpc::Status::OK;
		}
		else {
			return grpc::Status(grpc::StatusCode::UNKNOWN, "error occured");
		}
	}
	catch (std::exception& ex) {
		status = grpc::Status(grpc::StatusCode::UNKNOWN, ex.what());
	}

	return status;
}

grpc::Status GrpcServiceImplementation::BasicServerStreaming(
	grpc::ServerContext* context, 
	const ::basic_package::Request* request, 
	grpc::ServerWriter<basic_package::Reply>* writer) {

	std::cout << "BasicServerStreaming Called : " << std::endl;

	grpc::Status status;

	try {
		for (int i = 0; i < 10; i++) {
			basic_package::Reply reply;

			reply.set_value(request->value());

			writer->Write(reply);
		}

		status = grpc::Status::OK;
	}
	catch (std::exception& ex) {
		status = grpc::Status(grpc::StatusCode::UNKNOWN, ex.what());
	}

	return status;	
}

grpc::Status GrpcServiceImplementation::BasicClientStreaming(
	grpc::ServerContext* context,
	grpc::ServerReader<basic_package::Request>* reader,
	basic_package::Reply* reply) {

	std::cout << "BasicClientStreaming Called : " << std::endl;

	grpc::Status status;

	try {
		basic_package::Request request;

		while (reader->Read(&request)) {
			std::cout << request.value() << std::endl;
		}

		status = grpc::Status::OK;
	}
	catch (std::exception& ex) {
		status = grpc::Status(grpc::StatusCode::UNKNOWN, ex.what());
	}

	return status;
}

grpc::Status GrpcServiceImplementation::BasicBidirectionalStreaming(
	grpc::ServerContext* context,
	grpc::ServerReaderWriter<
	basic_package::Reply, 
	basic_package::Request>* stream) {

	std::cout << "BasicBidirectionalStreaming Called : " << std::endl;

	grpc::Status status;

	try {
		basic_package::Request request;
		
		while (stream->Read(&request)) {
			basic_package::Reply reply;
			reply.set_value(request.value());
			stream->Write(reply);
		}

		status = grpc::Status::OK;
	}
	catch (std::exception& ex) {
		status = grpc::Status(grpc::StatusCode::UNKNOWN, ex.what());
	}

	return status;
}

int main(int argc, char* argv[])
{
	try
	{
		int port = 50051;

		ServerBase server(port);

		GrpcServiceImplementation service;

		server.RegisterService(&service);
		server.Start();
		server.Wait();

		return 0;
	}
	catch (std::exception & ex)
	{
		std::cout << ex.what() << std::endl;

		return 1;
	}
}

