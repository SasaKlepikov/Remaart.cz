<article<?php print $attributes; ?>>
    <div<?php print $content_attributes; ?>>
        <?php
        // We hide the comments and links.
        hide($content['comments']);
        hide($content['links']);
        hide($content['product:commerce_price']);
        hide($content['product:field_bezna_cena']);
        print render($content);
        if ($content['product:field_bezna_cena']['#items'][0]['value'] > 0) {
          print render($content['product:field_bezna_cena']);
        }
        print "<div class='product-list-line'><strong>Naše cena:</strong> " . render($content['product:commerce_price']) . "</div>";
        ?>
    </div>
</article>