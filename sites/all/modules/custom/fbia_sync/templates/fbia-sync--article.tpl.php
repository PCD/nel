<!doctype html>
<html lang="en" prefix="op: http://media.facebook.com/op#">
  <head>
    <meta charset="utf-8">
    <link rel="canonical" href="<?php print $url;?>">
    <meta property="op:markup_version" content="v1.0">
    <meta property="fb:use_automatic_ad_placement" content="true">
  </head>
  <body>
    <article>
      <header>
        <?php if (isset($title) && !empty($title):?><h1><?php print $title;?></h1><?php endif; ?>
        <?php if (isset($sub_title) && !empty($sub_title):?><h2><?php print $sub_title;?></h2><?php endif; ?>

        <?php if (isset($published_date) && !empty($published_date):?>
        <time class="op-published" datetime="<?php print $published_date_r;?>"><?php print $published_date;?></time>
        <?php endif; ?>

        <?php if (isset($modified_date) && !empty($modified_date):?>
        <time class="op-modified" datetime="<?php print $modified_date_r;?>"><?php print $modified_date;?></time>
        <?php endif; ?>
        
        <?php if (isset($author) && !empty($author):?>
        <address>
          <?php print $author;?>
        </address>
        <?php endif; ?>

        <?php if (isset($image_main) && !empty($image_main):?>
        <figure>
          <img src="<?php print $image_main;?>" />
          <?php if (isset($image_main_alt) && !empty($image_main_alt)):?>
          <figcaption><?php print $image_main_alt;?></figcaption>
          <?php endif; ?>
        </figure>
        <?php endif; ?>

        <?php if (isset($breadcrumbs) && !empty($breadcrumbs)):?>
        <h3 class="op-kicker">
          <?php print $breadcrubms;?>
        </h3>
        <?php endif;?>
        
        <?php if (isset($ads) !empty($ads)):?>
        <section class="op-ad-template">
          <?php foreach ($ads as $ad):?>
          <figure class="op-ad">
            <iframe height="<?php print $ad['height'];?>" style="border:0;margin:0;padding:0;" width="<?php print $ad['width'];?>">
              <?php print $ad['code'];?>
            </iframe>
          </figure>
          <?php endforeach;?>
        </section>
        <?php endif; ?>
      </header>


      <?php if (isset($body) && !empty($body)):?>
      <section>
        <?php if (isset($video) && !empty($video)?><?php print $video;?><?php endif; ?>
        <?php print $body;?>
        
        <?php if (isset($slideshow) && !empty($slideshow):?>
        <figure class="op-slideshow">
          <?php foreach ($slideshow as $slideshow_item): ?>
          <figure>
            <img src="<?php print $slideshow_item['src'];?>" />
            <figcaption><?php print $slideshow_item['alt'];?></figcaption>
          </figure>
          <?php endforeach; ?>
        </figure>
        <?php endif; ?>
      </section>
      <?php endif; ?>

      <?php if (isset($add_2) && !empty($add_2)):?>
      <figure class="op-ad">
        <?php print $add_2;?>
      </figure>
      <?php endif;?>
    </article>
  </body>
</html>
