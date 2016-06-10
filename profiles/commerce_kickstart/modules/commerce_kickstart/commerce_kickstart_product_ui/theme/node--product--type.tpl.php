<article<?php print $attributes; ?>>
  <?php print $user_picture; ?>
  <?php print render($title_prefix); ?>
  <?php if (!$page && $title): ?>
  <header>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
  </header>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($display_submitted): ?>
  <footer class="submitted"><?php print $date; ?> -- <?php print $name; ?></footer>
  <?php endif; ?>
  <div class="container-24 grid-14 prefix-1 clearfix">
    <?php print render($content['product:field_images']); ?>
  </div>
  <div class="container-24 grid-8 prefix-1">
    <div<?php print $content_attributes; ?>>
      <?php
        // We hide the comments and links now so that we can render them later.
        hide($content['comments']);
        hide($content['links']);
        hide($content['product:field_description']);
        hide($content['product:field_rozmery_dilu_obrazu']);
        hide($content['field_original_image']);
        print render($content);
      ?>
    </div>
  </div>
  <div class="container-24 grid-24 clearfix">
    <?php
    $content['product:field_description']['#title'] = "hhh";
    print render($content['product:field_description']);
    print render($content['product:field_rozmery_dilu_obrazu']);
    print render($content['field_original_image']);
    ?>
  </div>
  <div class="container-24 grid-24 clearfix">
    <?php if (!empty($content['links'])): ?>
    <nav class="links node-links clearfix"><?php print render($content['links']); ?></nav>
    <?php endif; ?>
    <?php
    print render($content['comments']);
    ?>
  </div>
</article>
