#pragma once

#include <string>
#include <memory>
#include <grpcpp/grpcpp.h>
#include "core.hpp"

class ServerBase {
private:
    grpc::ServerBuilder builder_;
    std::unique_ptr<grpc::Server> server_;

    std::shared_ptr<grpc::ServerCredentials> get_credential_(Credential credential);

public:
    ServerBase(
        int port, 
        const std::string& ip = "0.0.0.0", 
        Credential credential = Credential::Insecure,
        grpc_compression_algorithm compression_algorithm = grpc_compression_algorithm::GRPC_COMPRESS_NONE,
        grpc_compression_level compression_level = grpc_compression_level::GRPC_COMPRESS_LEVEL_NONE);

    void RegisterService(grpc::Service* service);
    void Start();
    void Wait();
};

ServerBase::ServerBase(
    int port, 
    const std::string& ip, 
    Credential credential,
    grpc_compression_algorithm compression_algorithm,
    grpc_compression_level compression_level) {   

    std::string server_address(ip + ":" + std::to_string(port));
    builder_.AddListeningPort(server_address, get_credential_(credential));
    builder_.SetDefaultCompressionAlgorithm(compression_algorithm);
    builder_.SetDefaultCompressionLevel(compression_level);
}

void ServerBase::RegisterService(grpc::Service* service) {
    builder_.RegisterService(service);
}

void ServerBase::Start() {
    server_ = builder_.BuildAndStart();
}

void ServerBase::Wait() {
    server_->Wait();
}

std::shared_ptr<grpc::ServerCredentials> ServerBase::get_credential_(Credential credential) {
    switch (credential)
    {
    case Credential::Insecure:
        return grpc::InsecureServerCredentials();
    default:
        ///
        return grpc::InsecureServerCredentials();
    }
}
