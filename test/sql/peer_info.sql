CREATE TABLE "peer_info"
(
"id" INTEGER NOT NULL,
"source" CHAR(16),
"target" CHAR(16),
"ping_ok" INTEGER,
"create_time" TIMESTAMP(6) DEFAULT current_time NOT NULL,
"del" INTEGER DEFAULT 0,
PRIMARY KEY("id"));
