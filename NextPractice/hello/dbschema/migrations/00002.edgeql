CREATE MIGRATION m1vbxd6np4zeetkvuxtv6bdkyqkl3xag4dpidrmsti74z6s4amwsqq
    ONTO m1jbkm4y44e6nhehi3rzza5kfylv3ymj4iy6vx6fftwae3pj5523fq
{
  ALTER TYPE default::BlogPost {
      CREATE PROPERTY created_at: std::datetime {
          SET default := (std::datetime_of_statement());
          SET readonly := true;
      };
      CREATE PROPERTY updated_at: std::datetime {
          CREATE REWRITE
              INSERT 
              USING (std::datetime_of_statement());
          CREATE REWRITE
              UPDATE 
              USING (std::datetime_of_statement());
      };
  };
};
