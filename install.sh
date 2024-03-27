asset_dir=${1:-~/.local/share/geese}
bin_dir=${2:-~/.local/bin/geese}

mkdir -p $asset_dir 
mkdir -p $bin_dir 
cp ./geese.jpg $asset_dir
cp ./geese.wav $asset_dir
cp ./geese $bin_dir
chmod 755 $bin_dir/geese

# Optional: put bin_dir in your local path
# This is unnecessary if you already have it though

# pv='$PATH:${bin_dir/~/$HOME}'
# export PATH:=$pv

# Include the path code in your .profile to make a permanent change
# echo 'if [[ $PATH != *$pv* ]]; then export PATH:=$pv; fi;' >> ~/.profile

# The above except for all users
# echo 'if [[ $PATH != *$pv* ]]; then export PATH:=$pv; fi;' >> /etc/profile.d/geese.sh

