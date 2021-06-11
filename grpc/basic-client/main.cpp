#include <thread>
#include <grpcpp/grpcpp.h>

#include "basic.pb.h"
#include "basic.grpc.pb.h"
#include "../common/client_base.hpp"

class Client : public ClientBase {
private:
	std::unique_ptr<basic_package::BasicService::Stub> stub_;

public:
	Client(const std::string& ip, int port);
	void BasicUnary();
	void BasicServerStreaming();
	void BasicClientStreaming();
	void BasicBidirectionalStreaming();
};

Client::Client(const std::string& ip, int port) : ClientBase(ip, port) {
	stub_ = basic_package::BasicService::NewStub(ClientBase::channel_);
}

void Client::BasicUnary() {
	basic_package::Request request;
	basic_package::Reply reply;
	grpc::ClientContext context;

	grpc_compression_algorithm compression_algorithm = grpc_compression_algorithm::GRPC_COMPRESS_DEFLATE;

	context.set_compression_algorithm(GRPC_COMPRESS_DEFLATE);
	request.set_value("OK");

	grpc::Status status = stub_->BasicUnary(&context, request, &reply);
	if (!status.ok()) {
		std::cout 
			<< "Status : "
			<< status.error_code() << ": " << status.error_message()
			<< std::endl;
	}
	else {
		std::cout
			<< "Reply "
			<< reply.value() << " "
			<< std::endl;
	}
}

void Client::BasicServerStreaming() {
	grpc::ClientContext context;
	basic_package::Request request;
	request.set_value("value");

	std::unique_ptr<grpc::ClientReader<basic_package::Reply>> reader(
		stub_->BasicServerStreaming(&context, request));

	basic_package::Reply reply;

	while (reader->Read(&reply)) {
		std::cout << reply.value() << std::endl;
	}

	grpc::Status status = reader->Finish();
	if (!status.ok()) {
		std::cout 
			<< "Status : "
			<< status.error_code() << ": " << status.error_message()
			<< std::endl;
	}
	else {
		std::cout << "Success" << std::endl;
	}
}

void Client::BasicClientStreaming() {
	grpc::ClientContext context;
	basic_package::Request request;
	basic_package::Reply reply;

	request.set_value("value");

	std::unique_ptr<grpc::ClientWriter<basic_package::Request>> writer(
		stub_->BasicClientStreaming(&context, &reply));

	for (int i = 0 ; i < 10; i++) {
		if (!writer->Write(request))
			break;
	}

	writer->WritesDone();

	grpc::Status status = writer->Finish();
	if (!status.ok()) {
		std::cout 
			<< "Status : "
			<< status.error_code() << ": " << status.error_message()
			<< std::endl;
	}
	else {
		std::cout << "Success" << std::endl;
	}
}

void Client::BasicBidirectionalStreaming() {
	grpc::ClientContext context;

	// auto stream = std::make_shared<
	// grpc::ClientReaderWriter<
	// basic_package::Request, 
	// basic_package::Reply>>(stub_->BasicBidirectionalStreaming(&context));

	std::shared_ptr<grpc::ClientReaderWriter<
	basic_package::Request, 
	basic_package::Reply>> stream(stub_->BasicBidirectionalStreaming(&context));

	std::thread writer([stream]() {
		std::vector<basic_package::Request> requests;

		for (int i = 0 ; i < 100; i++) {
			basic_package::Request request;
			request.set_value("value");
			requests.emplace_back(request);
		}

		for (const auto& request : requests) {
			stream->Write(request);
		}
		stream->WritesDone();
	});

	basic_package::Reply reply;
	while (stream->Read(&reply)) {
		std::cout
			<< "Reply "
			<< reply.value() << " "
			<< std::endl;
	}
	writer.join();

	grpc::Status status = stream->Finish();
	if (!status.ok()) {
	std::cout 
		<< "Status"
		<< status.error_code() << ": " << status.error_message()
		<< std::endl;
	}
}

int main(int argc, char** argv) {
	Client client("127.0.0.1", 50051);

	for (int i = 0; i < 10000; i++) {
	client.BasicUnary();
	client.BasicServerStreaming();
	client.BasicClientStreaming();
	client.BasicBidirectionalStreaming();
	}
	return 0;
}
