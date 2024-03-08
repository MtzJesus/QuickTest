#include <iostream>
#include <memory>
#include <string>
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <grpcpp/grpcpp.h>
#include "example.grpc.pb.h"

ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using fc::Factorization;
using fc::FacRequest;
using fc::FacReply;

class FactorizationClient {
 public:
  FactorizationClient(std::shared_ptr<Channel> channel)
      : stub_(Factorization::NewStub(channel)) {}
      
  long CalFactor(const int& val) {
    FacRequest request;
    request.set_res(val);

    FacReply reply;

    ClientContext context;


    Status status = stub_->CalFactor(&context, request, &reply);

    if (status.ok()) {
      return reply.res();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Factorization::Stub> stub_;
};

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  std::string target_str = absl::GetFlag(FLAGS_target);
  FactorizationClient cli(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  int val = 5;
  long reply = cli.CalFactor(val);
  std::cout << "Fatorizatio \n" << val << " -> " << reply << std::endl;

  return 0;
}
