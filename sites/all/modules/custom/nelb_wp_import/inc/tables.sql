CREATE TABLE nelb_file (
  source_id INTEGER UNSIGNED NOT NULL, 
  source_blog INTEGER UNSIGNED NOT NULL, 
  guid VARCHAR(255) NOT NULL, 
  post_parent INTEGER UNSIGNED NOT NULL default 0, 
  fid INTEGER UNSIGNED NOT NULL, 
  FOREIGN KEY (fid) REFERENCES file_managed(fid) ON DELETE CASCADE, 
  PRIMARY KEY (source_id, source_blog)
);

CREATE TABLE nelb_post (
  source_id INTEGER UNSIGNED NOT NULL, 
  source_blog INTEGER UNSIGNED NOT NULL, 
  guid VARCHAR(255) NOT NULL, 
  nid INTEGER UNSIGNED NOT NULL, 
  FOREIGN KEY (nid) REFERENCES node(nid) ON DELETE CASCADE, 
  PRIMARY KEY (source_id, source_blog)
);

