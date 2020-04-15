#pragma comment(lib, "Ws2_32.lib")

#include <memory>
#include <grpcpp/grpcpp.h>
#include <grpcpp/grpcpp.h>

#include "basic.pb.h"
#include "basic.grpc.pb.h"

class GrpcServiceImplementation : public basic_package::BasicService::Service
{
private:
public:
	GrpcServiceImplementation() {}

	grpc::Status Function1(
		grpc::ServerContext* context,
		const basic_package::Request* request,
		basic_package::Reply* reply)
	{
		std::cout << "Function1 Called : " << request->value() << std::endl;

		basic_package::Status status;
		
		status.set_error("NULL");
		status.set_status("OK");

		//reply->set_allocated_status(&status);
		reply->set_value(request->value());

		return grpc::Status::OK;
	}
};

class GrpcService
{
private:
public:
	GrpcService() {}

	void run()
	{
		std::string address("0.0.0.0:50051");
		
		GrpcServiceImplementation service;
		
		grpc::ServerBuilder builder;

		builder.AddListeningPort(address, grpc::InsecureServerCredentials());
		
		builder.RegisterService(&service);
		
		std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

		std::cout << "Started" << std::endl;

		server->Wait();
	}
};

int main(int argc, char* argv[])
{
	try
	{
		GrpcService service;

		service.run();

		return 0;
	}
	catch (std::exception & ex)
	{
		std::cout << ex.what() << std::endl;

		return 1;
	}
}