#include "erl_nif.h"
#include "../deps/wflz/wfLZ.h"


//--
static 
ERL_NIF_TERM
erlang_produce_atom(ErlNifEnv* env, const char* name)
{
    ERL_NIF_TERM ret;

    if(enif_make_existing_atom(env, name, &ret, ERL_NIF_LATIN1)) 
    {
        return(ret);
    }

    return(enif_make_atom(env, name));
}


//--
static
ERL_NIF_TERM
erlang_produce_ok(ErlNifEnv* env, ERL_NIF_TERM msg)
{
    ERL_NIF_TERM term = erlang_produce_atom(env, "ok");
    return(enif_make_tuple2(env, term, msg));   
}


//--
static 
ERL_NIF_TERM
erlang_produce_error(ErlNifEnv* env, const char* msg)
{
    ERL_NIF_TERM term = erlang_produce_atom(env, "error");
    return(enif_make_tuple2(env, term, erlang_produce_atom(env, msg)));
}


//--
static 
ERL_NIF_TERM 
nif_fastcompress(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ErlNifBinary input;

    if(!enif_inspect_iolist_as_binary(env, argv[0], &input)) 
    {
        return(enif_make_badarg(env));
    }

    ErlNifBinary bin;

    // [rad] Figure out maximum compression buffer size.
    uint32_t compressed_bytes = wfLZ_GetMaxCompressedSize(input.size);

    // [rad] Get size of recommended scratchpad.
    uint32_t scratchpad_bytes = wfLZ_GetWorkMemSize();

    if(!enif_alloc_binary(compressed_bytes, &bin))
    {
        return(erlang_produce_error(env, "not_enough_memory"));
    }

    // [rad] Allocate scratchpad buffer.
    uint8_t* scratchpad = malloc(scratchpad_bytes);

    // [rad] Perform compression.
    uint32_t data_comp_size = wfLZ_CompressFast((const uint8_t* const) input.data, input.size, (uint8_t* const) bin.data, (const uint8_t*) scratchpad, 0);
     
    // [rad] We no longer need scratchpad.
    free(scratchpad);

    if(!data_comp_size)
    {
        return(erlang_produce_error(env, "compression_error"));
    }

    if(!enif_realloc_binary(&bin, data_comp_size)) 
    {
        return(erlang_produce_error(env, "not_enough_memory"));
    }

    return(enif_make_binary(env, &bin));
}


//--
static 
ERL_NIF_TERM 
nif_compress(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ErlNifBinary input;

    if(!enif_inspect_iolist_as_binary(env, argv[0], &input)) 
    {
        return(enif_make_badarg(env));
    }

    ErlNifBinary bin;

    // [rad] Figure out maximum compression buffer size.
    uint32_t compressed_bytes = wfLZ_GetMaxCompressedSize(input.size);

    // [rad] Get size of recommended scratchpad.
    uint32_t scratchpad_bytes = wfLZ_GetWorkMemSize();

    if(!enif_alloc_binary(compressed_bytes, &bin))
    {
        return(erlang_produce_error(env, "not_enough_memory"));
    }

    // [rad] Allocate scratchpad buffer.
    uint8_t* scratchpad = malloc(scratchpad_bytes);

    // [rad] Perform compression.
    uint32_t data_comp_size = wfLZ_Compress((const uint8_t* const) input.data, input.size, (uint8_t* const) bin.data, (const uint8_t*) scratchpad, 0);
     
    // [rad] We no longer need scratchpad.
    free(scratchpad);

    if(!data_comp_size)
    {
        return(erlang_produce_error(env, "compression_error"));
    }

    if(!enif_realloc_binary(&bin, data_comp_size)) 
    {
        return(erlang_produce_error(env, "not_enough_memory"));
    }

    return(enif_make_binary(env, &bin));
}


//-
static
ERL_NIF_TERM
nif_decompress(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ErlNifBinary input;

    if(!enif_inspect_iolist_as_binary(env, argv[0], &input)) 
    {
        return(enif_make_badarg(env));
    }

    ErlNifBinary bin;

    // [rad] Get decompressed size.
    uint32_t decompressed_bytes = wfLZ_GetDecompressedSize((const uint8_t* const) input.data);

    if(!decompressed_bytes)
    {
        return(erlang_produce_error(env, "not_compressed"));
    }

    // [rad] Create binary stream to hold decompressed data.
    if(!enif_alloc_binary(decompressed_bytes, &bin))
    {
        return(erlang_produce_error(env, "not_enough_memory"));
    } 

    // [rad] Perform decompression.
    wfLZ_Decompress((const uint8_t* const) input.data, bin.data);

    return(enif_make_binary(env, &bin));
}


//--
static 
ErlNifFunc 
nif_exports[] = 
{
    {"fastcompress",    1, nif_fastcompress},
    {"compress",        1, nif_compress},
    {"decompress",      1, nif_decompress},
};


//--
ERL_NIF_INIT(wflz, nif_exports, NULL, NULL, NULL, NULL)
