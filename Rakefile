
# Include directory for Erlang headers, usually something like /usr/lib/erlang/erts-5.8.1/include
DIR_ERLANG_INCLUDE = "/sdk/lib/erlang/usr/include"

task :default => [:help]

# List help.
desc "Help"
task :help do

    puts %x{rake --tasks}
end


# This will pull all the dependencies required by project.
desc "Download project dependencies"
task :deps do

    sh 'rebar get-deps'
end


# This will clean all binary files.
desc "Clean wflz-nif"
task :clean do

    sh 'rebar clean'
    sh 'rm -rf priv'
end

# This will compile erlang related code.
desc "Compile wflz-nif"
task :compile do

    sh 'rebar compile'
end


# This will compile the OS X 32 bit project.
desc "Compile OS X Darwin 32 bit"
task :darwin32 do

    if not Dir.exists? "priv"
        sh 'mkdir priv'
    end

    sh "gcc -undefined dynamic_lookup -dynamiclib -o priv/wflz.so src.c/wlfz_nif.c deps/wflz/wfLZ.c -I#{DIR_ERLANG_INCLUDE} -m32"
end


# This will compile the OS X 64 bit project.
desc "Compile OS X Darwin 32 bit"
task :darwin64 do

    if not Dir.exists? "priv"
        sh 'mkdir priv'
    end

    sh "gcc -undefined dynamic_lookup -dynamiclib -o priv/wflz.so src.c/wlfz_nif.c deps/wflz/wfLZ.c -I#{DIR_ERLANG_INCLUDE} -m64"
end
