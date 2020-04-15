#include <grpcpp/grpcpp.h>

#include "basic.pb.h"
#include "basic.grpc.pb.h"

class Client
{
private:
	std::unique_ptr<basic_package::BasicService::Stub> _stub;
public:
	Client(std::shared_ptr<grpc::Channel> channel)
		: _stub(basic_package::BasicService::NewStub(channel)) {}

	void run() {
		basic_package::Request request;
		basic_package::Reply reply;
		grpc::ClientContext context;

		request.set_value("Hello");

		grpc::Status status = _stub->Function1(&context, request, &reply);
		if (!status.ok())
		{
			std::cout 
				<< "Status"
				<< status.error_code() << ": " << status.error_message()
				<< std::endl;
		}
		else
		{

			std::cout
				<< "Reply "
				<< reply.value() << " "
				<< reply.status().error() << " "
				<< reply.status().status() 
				<< std::endl;
		}
	}
};

int main(int argc, char** argv) {
	Client client(
		grpc::CreateChannel(
			"localhost:50051",
			grpc::InsecureChannelCredentials()));

	client.run();

	return 0;
}
