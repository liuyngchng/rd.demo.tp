CREATE TABLE "topo_info"
(
"id" INTEGER NOT NULL,
"source" VARCHAR(128),
"target" VARCHAR(128),
"loss" INTEGER,
"is_connected" INTEGER,
"available_bw" INTEGER,
"capacity_bw" INTEGER,
"latency" INTEGER,
"type" INTEGER,
PRIMARY KEY("id"));
