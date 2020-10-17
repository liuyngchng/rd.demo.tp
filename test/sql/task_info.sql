CREATE TABLE "task_info"
(
"id" INTEGER,
"app_id" INTEGER,
"data_size" INTEGER,
"uid" VARCHAR(128),
"target" VARCHAR(128),
"ZONE" INTEGER,
"create_time" TIMESTAMP(6) DEFAULT CURRENT_TIME NOT NULL,
"update_time" TIMESTAMP(6),
"interrupt_time" TIMESTAMP(6),
"restart_time" TIMESTAMP(6),
"cancel_time" TIMESTAMP(6),
"file_id" VARCHAR(128),
"priority" INTEGER,
"progress" INTEGER,
"op_uid" VARCHAR(128),
"op_type" INTEGER,
"status" INTEGER,
"data_rate" INTEGER,
"del" INTEGER DEFAULT 0) ;

