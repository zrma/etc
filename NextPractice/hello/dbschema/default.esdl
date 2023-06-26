module default {
  type BlogPost {
    required title: str;
    required content: str {
      default := ""
    };
    created_at: datetime {
      readonly := true;
      default := datetime_of_statement();
    }
    updated_at: datetime {
      rewrite insert, update using (datetime_of_statement());
    }
  }
}