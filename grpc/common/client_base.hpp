#pragma once

#include <grpcpp/grpcpp.h>
#include "core.hpp"

class ClientBase {
private:
    std::shared_ptr<grpc::ChannelCredentials> get_credential_(Credential credential);
    std::string get_load_balancing_policy_(LoadBalancingPolicy load_balancing_policy);

protected:
    std::shared_ptr<grpc::Channel> channel_;

public:
    ClientBase(
        const std::string& ip, 
        int port, 
        Credential credential = Credential::Insecure,
        LoadBalancingPolicy load_balancing_policy = LoadBalancingPolicy::RoundRobin,
        grpc_compression_algorithm compression_algorithm = grpc_compression_algorithm::GRPC_COMPRESS_NONE);
};

ClientBase::ClientBase(
    const std::string& ip, 
    int port, 
    Credential credential,
    LoadBalancingPolicy load_balancing_policy,
    grpc_compression_algorithm compression_algorithm) {

    std::string server_address(ip + ":" + std::to_string(port));

    grpc::ChannelArguments channel_args;
    channel_args.SetCompressionAlgorithm(compression_algorithm);
    // channel_args.SetLoadBalancingPolicyName(
    //     get_load_balancing_policy_(load_balancing_policy));

    channel_ = grpc::CreateCustomChannel(
        server_address, 
        get_credential_(credential), 
        channel_args);
}

std::string get_load_balancing_policy_(LoadBalancingPolicy load_balancing_policy) {
    switch (load_balancing_policy)
    {
    case LoadBalancingPolicy::RoundRobin:
        return std::string("round_robin");
        break;
    default:
        ///
        break;
    }
}

std::shared_ptr<grpc::ChannelCredentials> ClientBase::get_credential_(Credential credential) {
    switch (credential)
    {
    case Credential::Insecure:
        return grpc::InsecureChannelCredentials();
    default:
        ///
        return grpc::InsecureChannelCredentials();
    }
}
