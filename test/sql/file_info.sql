CREATE TABLE "file_info"
(
"id" INTEGER NOT NULL,
"app_id" INTEGER,
"file_id" INTEGER,
"name" VARCHAR(128),
"size" INTEGER,
"path" VARCHAR(128),
"slice_size" INTEGER,
"slice_total" INTEGER,
"slice_snd" INTEGER,
"md5" CHAR(32),
"create_time" TIMESTAMP(6) DEFAULT CURRENT_TIME NOT NULL,
"update_time" TIMESTAMP(6),
"del" INTEGER DEFAULT 0,
PRIMARY KEY("id"));
