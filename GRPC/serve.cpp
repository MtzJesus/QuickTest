#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include "example.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using fc::Factorization;
using fc::FacRequest;
using fc::FacReply;

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");


class FactorizationServiceImpl final : public Factorization::Service {
  Status CalFactor(ServerContext* context, const FacRequest* request,
                  FacReply* reply) override {
    int num = request->res();
    long acc;
    if(num <= 10){
        for(unsigned int i = num-1; i > 0;i--){
            acc*=i;
        }
    } else acc=0;
    std::string prefix("Hello ");
    reply->set_res(acc);
    return Status::OK;
  }
};

void RunServer(uint16_t port) {
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  FactorizationServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
