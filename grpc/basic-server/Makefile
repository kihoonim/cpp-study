CXX = g++ -std=c++17 #-static-libgcc -static-libstdc++ 
GRPC_HOME = /mnt/c/workspace/wsl/grpc

GRPC_INCLUDE = $(GRPC_HOME)/include
GRPC_LIB = $(GRPC_HOME)/cmake/build

PROTOBUF_INCLUDE = $(GRPC_HOME)/third_party/protobuf/src
PROTOBUF_LIB = $(GRPC_HOME)/cmake/build/third_party/protobuf
BORINGSSL_LIB = $(GRPC_HOME)/cmake/build/third_party/boringssl-with-bazel
CARES_LIB = $(GRPC_HOME)/cmake/build/third_party/cares/cares/lib
ZLIB_LIB = $(GRPC_HOME)/cmake/build/third_party/zlib
RE2_LIB = $(GRPC_HOME)/cmake/build/third_party/re2
ABSL_BASE_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/base
ABSL_CONTAINER_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/container
ABSL_DEBUGGING_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/debugging
ABSL_FLAGS_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/flags
ABSL_HASH_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/hash
ABSL_NUMERIC_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/numeric
ABSL_RANDOM_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/random
ABSL_STATUS_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/status
ABSL_STRING_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/strings
ABSL_SYNCHRONIZATION_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/synchronization
ABSL_TIME_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/time
ABSL_TYPES_LIB = $(GRPC_HOME)/cmake/build/third_party/abseil-cpp/absl/types

INCLUDE_FLAG += -I$(GRPC_INCLUDE) 
INCLUDE_FLAG += -I$(PROTOBUF_INCLUDE)

LIB_FLAG += -L$(GRPC_LIB) \
-lgrpc++ \
-lgrpc \
-lgpr \
-laddress_sorting \
-lgrpc_unsecure \
-lgrpc++_alts \
-lgrpc++_error_details \
-lgrpc++_reflection \
-lgrpc++_unsecure \
-lgrpcpp_channelz \
-lupb

LIB_FLAG += -L$(PROTOBUF_LIB) \
-lprotobuf \
-lprotobuf-lite \
-lprotoc \

LIB_FLAG += -L$(BORINGSSL_LIB) \
-lssl \
-lcrypto \

LIB_FLAG += -L$(CARES_LIB) \
-lcares \

LIB_FLAG += -L$(ZLIB_LIB) \
-lz \

LIB_FLAG += -L$(RE2_LIB) \
-lre2 \
-ltesting \

LIB_FLAG += -L$(ABSL_SYNCHRONIZATION_LIB) \
-labsl_synchronization \
-labsl_graphcycles_internal \

LIB_FLAG += -L$(ABSL_BASE_LIB) \
-labsl_cord \
-labsl_str_format_internal \
-labsl_strings \
-labsl_strings_internal \

LIB_FLAG += -L$(ABSL_CONTAINER_LIB) \
-labsl_hashtablez_sampler \
-labsl_raw_hash_set \

LIB_FLAG += -L$(ABSL_DEBUGGING_LIB) \
-labsl_symbolize \
-labsl_stacktrace \
-labsl_debugging_internal \
-labsl_demangle_internal \
-labsl_examine_stack \
-labsl_failure_signal_handler \
-labsl_leak_check \
-labsl_leak_check_disable \

LIB_FLAG += -L$(ABSL_FLAGS_LIB) \
-labsl_flags \
-labsl_flags_commandlineflag \
-labsl_flags_commandlineflag_internal \
-labsl_flags_config \
-labsl_flags_internal \
-labsl_flags_marshalling \
-labsl_flags_parse \
-labsl_flags_private_handle_accessor \
-labsl_flags_program_name \
-labsl_flags_reflection \
-labsl_flags_usage \
-labsl_flags_usage_internal \

LIB_FLAG += -L$(ABSL_HASH_LIB) \
-labsl_city \
-labsl_hash \

LIB_FLAG += -L$(ABSL_NUMERIC_LIB) \
-labsl_int128 \

LIB_FLAG += -L$(ABSL_RANDOM_LIB) \
-labsl_random_distributions \
-labsl_random_internal_distribution_test_util \
-labsl_random_internal_platform \
-labsl_random_internal_pool_urbg \
-labsl_random_internal_randen \
-labsl_random_internal_randen_hwaes \
-labsl_random_internal_randen_hwaes_impl \
-labsl_random_internal_randen_slow \
-labsl_random_internal_seed_material \
-labsl_random_seed_gen_exception \
-labsl_random_seed_sequences \

LIB_FLAG += -L$(ABSL_STATUS_LIB) \
-labsl_status \
-labsl_statusor \

LIB_FLAG += -L$(ABSL_STRING_LIB) \
-labsl_base \
-labsl_exponential_biased \
-labsl_log_severity \
-labsl_malloc_internal \
-labsl_periodic_sampler \
-labsl_raw_logging_internal \
-labsl_scoped_set_env \
-labsl_spinlock_wait \
-labsl_strerror \
-labsl_throw_delegate \

LIB_FLAG += -L$(ABSL_TIME_LIB) \
-labsl_civil_time \
-labsl_time \
-labsl_time_zone \

LIB_FLAG += -L$(ABSL_TYPES_LIB) \
-labsl_bad_any_cast_impl \
-labsl_bad_optional_access \
-labsl_bad_variant_access \

LIB_FLAG += -lpthread

EXEC_NAME = basic_server

all: release

release: CXX += -O2
release: exec

debug: CXX += -g -DDEBUG
debug: exec

exec: data.pb.o data.grpc.pb.o basic.pb.o basic.grpc.pb.o 
	@echo "[Exec] Start"
	@$(CXX) --version
	@$(CXX) main.cpp -o $(EXEC_NAME) $(INCLUDE_FLAG) $^ $(LIB_FLAG)
	@echo "[Exec] End"

data.pb.o: data.pb.cc
	$(CXX) $(INCLUDE_FLAG) -c $^ -o $@

data.grpc.pb.o: data.grpc.pb.cc
	$(CXX) $(INCLUDE_FLAG) -c $^ -o $@

basic.pb.o: basic.pb.cc
	$(CXX) $(INCLUDE_FLAG) -c $^ -o $@

basic.grpc.pb.o: basic.grpc.pb.cc
	$(CXX) $(INCLUDE_FLAG) -c $^ -o $@

PROTOC = $(PROTOBUF_LIB)/protoc
GRPC_CPP_PLUGIN_PATH = $(GRPC_LIB)/grpc_cpp_plugin
PROTO_PATH = ../proto

data.pb.cc:
	@$(PROTOC) -I $(PROTO_PATH) --proto_path=$(PROTO_PATH) --cpp_out=. $(PROTO_PATH)/data.proto

data.grpc.pb.cc:
	@$(PROTOC) -I $(PROTO_PATH) --proto_path=$(PROTO_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $(PROTO_PATH)/data.proto

basic.pb.cc:
	@$(PROTOC) -I $(PROTO_PATH) --proto_path=$(PROTO_PATH) --cpp_out=. $(PROTO_PATH)/basic.proto

basic.grpc.pb.cc:
	@$(PROTOC) -I $(PROTO_PATH) --proto_path=$(PROTO_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $(PROTO_PATH)/basic.proto


clean:
	@echo "[Clean] Start"
	@rm -f ./$(EXEC_NAME)
	@rm -f ./*.o
	@rm -f ./*.pb.cc ./*.pb.h
	@echo "[Clean] End"