\l Tx/conf/cfftbase.q

\d .db
R:([id:`symbol$()] name:`symbol$(); func:()); /role
U:([id:`symbol$()] name:`symbol$(); role:`symbol$(); passwd:`symbol$(); online:`boolean$(); h:`long$(); loginip:`symbol$(); logintime:`timestamp$(); logouttime:`timestamp$();calltime:`timestamp$(); callfunc:`symbol$()); /user
SG:([id:`symbol$()] name:`symbol$(); admin:`symbol$(); items:()); /Strategy Group 
S:([id:`symbol$()] name:`symbol$(); sgroup:`symbol$(); ft:`symbol$(); ftlocal:`symbol$(); fts:(); users:()); /Strategy 
\d .
