$(document).ready(function() {
    const siteBUrl = "https://example.com"; // Substitua pelo endereço do site B
    const targetDivId = "#target-div"; // Substitua pelo ID da div específica no site B

    // Verifica se o site B está disponível
    $.ajax({
        url: siteBUrl,
        method: "GET",
        success: function(data) {
            // Cria um elemento temporário para buscar o conteúdo da div específica
            const tempDiv = $("<div>").html(data);
            const targetContent = tempDiv.find(targetDivId).html();

            if (targetContent) {
                // Atualiza o conteúdo da div no site A
                $("#content").html(targetContent);
            } else {
                $("#content").html("O conteúdo não foi encontrado no site B.");
            }
        },
        error: function() {
            $("#content").html("O site B não está acessível no momento.");
        }
    });
});