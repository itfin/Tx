unlink ../tick.q ; ln -s Tx/core/tick.q ../
unlink ../tick ; ln -s Tx/tick ../
unlink ../tick/api.q ; ln -s ../Tx/core/api.q ../tick/
find ../l64 -type l -exec unlink {} \;  ;  ln -s ../Tx/ext/dll/l64/* ../l64/



