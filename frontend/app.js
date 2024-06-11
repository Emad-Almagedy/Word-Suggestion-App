document.getElementById('wordForm').addEventListener('submit', async function(event) {
    event.preventDefault();
    const word = document.getElementById('wordInput').value;
    const suggestionsDiv = document.getElementById('suggestions');

    try {
        const response = await fetch('http://127.0.0.1:5000/get_suggestions', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ word: word })
        });

        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        const data = await response.json();
        suggestionsDiv.innerHTML = '';

        if (data.error) {
            suggestionsDiv.innerHTML = `Error: ${data.error}<br>Details: ${data.details}`;
        } else {
            const suggestions = data.suggestions;
            suggestionsDiv.innerHTML = '<ul>' + suggestions.map(s => `<li>${s}</li>`).join('') + '</ul>';
        }
    } catch (error) {
        suggestionsDiv.innerHTML = `Error fetching suggestions. Please try again later.<br>Details: ${error.message}`;
    }
});
