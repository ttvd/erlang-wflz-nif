
# Helper function used to figure out location of erlang headers.
def erlang_headers

    loc = %x{which erl}
    
    if loc.empty?

        puts "Error locating erlang erl binary, make sure it's in the path."
        exit
    end

    idx = loc.index('/bin')

    if not idx

        puts "Invalid erlang path, make sure installation is correct."
        exit
    end

    "#{loc[0, idx]}/lib/erlang/usr/include"
end



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

# This will compile the linux 32 bit project.
desc "Compile Linux 32 bit"
task :linux32 do

    if not Dir.exists? "priv"
        sh 'mkdir priv'
    end

    sh "gcc -o priv/wflz.so -fpic -shared src.c/wlfz_nif.c deps/wflz/wfLZ.c -I#{erlang_headers} -m32"
end


# This will compile the linux 32 bit project.
desc "Compile Linux 64 bit"
task :linux64 do

    if not Dir.exists? "priv"
        sh 'mkdir priv'
    end

    sh "gcc -o priv/wflz.so -fpic -shared src.c/wlfz_nif.c deps/wflz/wfLZ.c -I#{erlang_headers} -m64"
end


# This will compile the OS X 32 bit project.
desc "Compile OS X Darwin 32 bit"
task :darwin32 do

    if not Dir.exists? "priv"
        sh 'mkdir priv'
    end

    sh "gcc -undefined dynamic_lookup -dynamiclib -o priv/wflz.so src.c/wlfz_nif.c deps/wflz/wfLZ.c -I#{erlang_headers} -m32"
end


# This will compile the OS X 64 bit project.
desc "Compile OS X Darwin 32 bit"
task :darwin64 do

    if not Dir.exists? "priv"
        sh 'mkdir priv'
    end

    sh "gcc -undefined dynamic_lookup -dynamiclib -o priv/wflz.so src.c/wlfz_nif.c deps/wflz/wfLZ.c -I#{erlang_headers} -m64"
end
