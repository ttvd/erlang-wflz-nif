-module(wflz).

-export([compress/1, fastcompress/1, decompress/1]).
-export([init/0]).

-on_load(init/0).

init() ->
    ok = erlang:load_nif("./priv/wflz", 0).

compress(_) ->
    not_loaded(?LINE).

fastcompress(_) ->
    not_loaded(?LINE).

decompress(_) ->
    not_loaded(?LINE).

not_loaded(Line) ->
    exit({nif_library_not_loaded, [{module, ?MODULE}, {line, Line}]}).
